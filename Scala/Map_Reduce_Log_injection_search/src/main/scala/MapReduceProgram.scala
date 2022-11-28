import org.apache.hadoop.fs.Path
import org.apache.hadoop.conf.*
import org.apache.hadoop.io.*
import org.apache.hadoop.util.*
import org.apache.hadoop.mapred.*
import org.apache.hadoop.mapreduce.Job
import org.apache.hadoop.io.WritableComparator
import org.apache.hadoop.mapreduce.OutputFormat
import org.apache.hadoop.mapreduce.InputFormat

import HelperUtils.{CreateLogger, Parameters}

import java.io.IOException
import java.util
import scala.jdk.CollectionConverters.*

import java.text.SimpleDateFormat
import com.github.nscala_time.time.Imports._


// creating an object for the map reduce tasks
object MapReduceProgram:
  import HelperUtils.Parameters.*

  private val logger = CreateLogger(classOf[MapReduceProgram.type]) // creating a logger for it

  // getting the start and end time and converting it to time value
  private val timeStartArr = Parameters.startTime.split(":")
  private val timeEndArr = Parameters.endTime.split(":")
  private val time_start = (timeStartArr(0).toInt).hours + (timeStartArr(1).toInt).minutes + ((timeStartArr(2).toInt).seconds)
  private val time_end = (timeEndArr(0).toInt).hours + (timeEndArr(1).toInt).minutes + ((timeEndArr(2).toInt).seconds)
  private val time_diff = (time_end - time_start).millis // the time window/interval to check
  private val interval = Parameters.interval // the value to create intervals in the window from

  // mapper for task 1
  // takes in a line as value and produces key value pairs of each type of message and value 1
  // if the message is of the regex type defined
  class Map1 extends MapReduceBase with Mapper[LongWritable, Text, Text, IntWritable]:
    private final val one = new IntWritable(1)
    private val word = new Text()

    @throws[IOException]
    def map(key: LongWritable, value: Text, output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      val line:  String = value.toString // get the line
      val arr = line.split(" ") // creating array by splitting the log line by spaces


      // checking if the log message matches the regular expression
      if (arr(arr.length - 1).matches(Parameters.regex)) then {
        val time = arr(0).split(":") // splitting the current time string into array and calculating the time since the start time
        val diff = ((time(0).toInt).hours + (time(1).toInt).minutes + ((time(2).substring(0, 2)).toInt).seconds - time_start).millis

        // if the log message is in the time window
        if diff >= 0 && diff < time_diff then {
          word.set(arr(2)) // setting the word to current message type
          logger.debug(s"found entry in the time interval for $word")
          output.collect(word, one) // collect the entry as key: message type, value: 1 (one message encountered)
        }
      }

  // reducer for task 1
  // takes in all the values accumulated for each key and adds all the values to get the total number of log for the message type
  class Reduce1 extends MapReduceBase with Reducer[Text, IntWritable, Text, IntWritable]:
    private final val one = new IntWritable(1)
    override def reduce(key: Text, values: util.Iterator[IntWritable], output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      // getting the sum of all the values for the message type
      val sum = values.asScala.reduce((valueOne, valueTwo) => new IntWritable(valueOne.get() + valueTwo.get()))

      if (sum.get() < 0) { // error in getting the sum
        logger.error(s"failed to get the number of logs for the entry: $key")
      } else {
        logger.debug(s"total $sum entries found for key $key")
        output.collect(key, new IntWritable(sum.get()))
      }


  // mapper for task 2
  class Map2 extends MapReduceBase with Mapper[LongWritable, Text, IntWritable, IntWritable] :
    private final val one = new IntWritable(1)
    private val word = new Text()
    private val period = new IntWritable(0)

    @throws[IOException]
    def map(key: LongWritable, value: Text, output: OutputCollector[IntWritable, IntWritable], reporter: Reporter): Unit =
      val line: String = value.toString // get the line
      val arr = line.split(" ") // creating array by splitting the log line by spaces

      // checking if the log message matches the regular expression
      if (arr(arr.length - 1).matches(Parameters.regex)) then {

        val time = arr(0).split(":")
        val diff = ((time(0).toInt).hours + (time(1).toInt).minutes + ((time(2).substring(0, 2)).toInt).seconds - time_start).millis

        // if the log message is in the time window
        if diff >= 0 && diff < time_diff && arr(2) == "ERROR" then {
          logger.debug("found entry in the time interval")

          period.set((diff / interval).toInt)
          output.collect(period, one)
        }
      }

  // reducer for task 2
  class Reduce2 extends MapReduceBase with Reducer[IntWritable, IntWritable, IntWritable, IntWritable] :
    override def reduce(key: IntWritable, values: util.Iterator[IntWritable], output: OutputCollector[IntWritable, IntWritable], reporter: Reporter): Unit =
      val sum = values.asScala.reduce((valueOne, valueTwo) => new IntWritable(valueOne.get() + valueTwo.get())) // summing all logs for each interval
      output.collect(key, new IntWritable(sum.get()))


  // helper class for the mapreduce 2, this class flips the key value pairs and thus
  // produces they key: number of messages in the interval, value: the number of interval
  class Map2h extends MapReduceBase with Mapper[LongWritable, Text, IntWritable, IntWritable] :

    @throws[IOException]
    def map(key: LongWritable, value: Text, output: OutputCollector[IntWritable, IntWritable], reporter: Reporter): Unit =
      val keyval = value.toString.split(",") // get the line and split by comma, as its a csv
      output.collect(new IntWritable(keyval(1).toInt), new IntWritable(keyval(0).toInt)) // flip the key value pair

  // helper for mapreduce 2, this class collects the flipped key values, since some intervals might have the same
  // number of errors we loop over all the list of intervals that have the same number of errors
  class Reduce2h extends MapReduceBase with Reducer[IntWritable, IntWritable, IntWritable, IntWritable] :
    override def reduce(key: IntWritable, values: util.Iterator[IntWritable], output: OutputCollector[IntWritable, IntWritable], reporter: Reporter): Unit =
      values.asScala.foreach(value => output.collect(key, value)) // loop over and add


  // comparator for helper mapred2
  // comparator class to compare the keys: number of error messages and produce an int to
  // sort in descending order
  class myComparator protected() extends WritableComparator(classOf[IntWritable], true) {
    override def compare(w1: WritableComparable[_], w2: WritableComparable[_]): Int = {
      val v1 = w1.asInstanceOf[IntWritable].get()
      val v2 = w2.asInstanceOf[IntWritable].get()

      if v1 < v2 then 1
      else if v1 == v2 then 0
      else -1
    }
  }


  // mapper for task 3
  // takes in each line as a value and maps it to key: message type, value 1
  class Map3 extends MapReduceBase with Mapper[LongWritable, Text, Text, IntWritable] :
    private final val one = new IntWritable(1)
    private val word = new Text()

    @throws[IOException]
    def map(key: LongWritable, value: Text, output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      val line = value.toString // get the line
      val arr = line.split(" ") // creating array by splitting the log line by space

      word.set(arr(2))
      output.collect(word, one) // collect the entry as one of the message type

  // reduce for taks 3
  // takes in key: message type and value: list of all values by mapper and counts
  // the total number of instances of the message type and collects it
  class Reduce3 extends MapReduceBase with Reducer[Text, IntWritable, Text, IntWritable] :
    override def reduce(key: Text, values: util.Iterator[IntWritable], output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      val sum = values.asScala.reduce((valueOne, valueTwo) => new IntWritable(valueOne.get() + valueTwo.get())) // get the sum of all the values
      output.collect(key, new IntWritable(sum.get())) // collect the message type with the total number of logs

  // mapper for task 4
  // takes in a line as a value and maps it to key: message type and value: number of chars in the message
  // if the message is of the regex type defined
  class Map4 extends MapReduceBase with Mapper[LongWritable, Text, Text, IntWritable] :
    private final val chars = new IntWritable(1)
    private val word = new Text()

    @throws[IOException]
    def map(key: LongWritable, value: Text, output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      val line: String = value.toString // get the line
      val arr = line.split(" ") // creating array by splitting the log line by space

      // checking if the log message matches the regular expression
      if (arr(arr.length - 1).matches(Parameters.regex)) then {
        word.set(arr(2)) // the message type
        chars.set(arr(arr.length - 1).length) // the number of chars in the message
        output.collect(word, chars) // collect the message type and the number of chars in it
      }

  // reducer for task 4
  // takes in key: the message type and value: list of number of chars for all instances and reduces it to
  // key: message type, value: the maximum number of chars in one of all of the instance and collects it
  class Reduce4 extends MapReduceBase with Reducer[Text, IntWritable, Text, IntWritable] :
    override def reduce(key: Text, values: util.Iterator[IntWritable], output: OutputCollector[Text, IntWritable], reporter: Reporter): Unit =
      val maxi = values.asScala.reduce((x, y) => new IntWritable(x.get() max y.get())) // get the max (number of chars in an instance)
      output.collect(key, new IntWritable(maxi.get())) // collect it

  // our main function
  @main def runMapReduce(inputPath: String, outputPath: String, choice: Int, outputPath2: String = "") =
    logger.info("Welcome to my Map Reduce Program")
    logger.info("Setting up the map-reduce")


    // matching the input and performing the task required
    choice match
      case 1 => { // first task

        val conf: JobConf = new JobConf(this.getClass) // creating a job configuration
        conf.setJobName("Homework1")
        conf.set("mapreduce.job.maps", "1")
        conf.set("mapreduce.job.reduces", "1")
        conf.set("mapreduce.output.textoutputformat.separator", ",")

        // setting the class types
        conf.setOutputKeyClass(classOf[Text])
        conf.setOutputValueClass(classOf[IntWritable])
        logger.info("option one chosen, proceeding with option 1 map-reduce")
        conf.setMapperClass(classOf[Map1])
        conf.setCombinerClass(classOf[Reduce1])
        conf.setReducerClass(classOf[Reduce1])

        conf.setInputFormat(classOf[TextInputFormat])
        conf.setOutputFormat(classOf[TextOutputFormat[Text, IntWritable]])
        FileInputFormat.setInputPaths(conf, new Path(inputPath))
        FileOutputFormat.setOutputPath(conf, new Path(outputPath))

        // running the job
        JobClient.runJob(conf)
      }
      case 2 => { // second task
        logger.info("option two chosen, proceeding with option 2 map-reduce")

        // check for correct 2nd output path
        if outputPath2 == "" then {
          logger.error("please specify a correct second output path for map-reduce task 2")
        } else {

          // settings for job 1: map the intervals with their number of error messages
          val conf: JobConf = new JobConf(this.getClass)
          conf.set("mapreduce.job.maps", "1")
          conf.set("mapreduce.job.reduces", "1")
          conf.set("mapreduce.output.textoutputformat.separator", ",")

          conf.setMapperClass(classOf[Map2])
          conf.setCombinerClass(classOf[Reduce2])
          conf.setReducerClass(classOf[Reduce2])
          conf.setInputFormat(classOf[TextInputFormat])
          conf.setOutputFormat(classOf[TextOutputFormat[IntWritable, IntWritable]])
          conf.setOutputKeyClass(classOf[IntWritable])
          conf.setOutputValueClass(classOf[IntWritable])
          FileInputFormat.setInputPaths(conf, new Path(inputPath))
          FileOutputFormat.setOutputPath(conf, new Path(outputPath))

          val job = Job.getInstance(conf, "Homework1")
          job.setJarByClass(this.getClass)

          logger.info("starting job 1: to match the intervals with their number of error messages")

          // we wait for the completion of job 1 as job 2 needs the input from job 1's output
          job.waitForCompletion(true)
          logger.info("job 1 finished")

          val conf2: JobConf = new JobConf(this.getClass)
          conf2.set("mapreduce.job.maps", "1")
          conf2.set("mapreduce.job.reduces", "1")
          conf2.set("mapreduce.output.textoutputformat.separator", ",")

          conf2.setMapperClass(classOf[Map2h])
          conf2.setCombinerClass(classOf[Reduce2h])
          conf2.setReducerClass(classOf[Reduce2h])
          conf2.setInputFormat(classOf[TextInputFormat])
          conf2.setOutputFormat(classOf[TextOutputFormat[IntWritable, IntWritable]])
          conf2.setOutputKeyClass(classOf[IntWritable])
          conf2.setOutputValueClass(classOf[IntWritable])

          // input path for second job is to get the outptut of the first job, and this is going to be in the part-0000 of outputpath1
          FileInputFormat.setInputPaths(conf2, new Path(outputPath + "/part-00000"))
          FileOutputFormat.setOutputPath(conf2, new Path(outputPath2)) // second outputpath

          logger.info("starting job 2: to sort the intervals by descending order of nunmber of messages")
          val job2 = Job.getInstance(conf2, "Homework1")
          job2.setJarByClass(this.getClass)
          job2.setSortComparatorClass(classOf[myComparator])

          logger.info("option two chosen, proceeding with option 2 map-reduce")

          job2.waitForCompletion(true)
        }

      }
      case 3 => { // third task

        val conf: JobConf = new JobConf(this.getClass) // creating a job configuration
        conf.setJobName("Homework1")
        conf.set("mapreduce.job.maps", "1")
        conf.set("mapreduce.job.reduces", "1")
        conf.set("mapreduce.output.textoutputformat.separator", ",")

        // setting the class types
        conf.setOutputKeyClass(classOf[Text])
        conf.setOutputValueClass(classOf[IntWritable])
        logger.info("option four chosen, proceeding with option 4 map-reduce")
        conf.setMapperClass(classOf[Map3])
        conf.setCombinerClass(classOf[Reduce3])
        conf.setReducerClass(classOf[Reduce3])

        conf.setInputFormat(classOf[TextInputFormat])
        conf.setOutputFormat(classOf[TextOutputFormat[Text, IntWritable]])
        FileInputFormat.setInputPaths(conf, new Path(inputPath))
        FileOutputFormat.setOutputPath(conf, new Path(outputPath))

        // running the job
        JobClient.runJob(conf)
      }
      case 4 => { // fourth task

        val conf: JobConf = new JobConf(this.getClass) // creating a job configuration
        conf.setJobName("Homework1")
        conf.set("mapreduce.job.maps", "1")
        conf.set("mapreduce.job.reduces", "1")
        conf.set("mapreduce.output.textoutputformat.separator", ",")

        // setting the class types
        conf.setOutputKeyClass(classOf[Text])
        conf.setOutputValueClass(classOf[IntWritable])
        logger.info("option four chosen, proceeding with option 4 map-reduce")
        conf.setMapperClass(classOf[Map4])
        conf.setCombinerClass(classOf[Reduce4])
        conf.setReducerClass(classOf[Reduce4])

        conf.setInputFormat(classOf[TextInputFormat])
        conf.setOutputFormat(classOf[TextOutputFormat[Text, IntWritable]])
        FileInputFormat.setInputPaths(conf, new Path(inputPath))
        FileOutputFormat.setOutputPath(conf, new Path(outputPath))

        // running the job
        JobClient.runJob(conf)
      }
      case _ => { // invalid entry
        logger.error("Invalid choice entry, please enter a correct choice of map reduce, please use \"inputPath outputPath choice\" as the input arguements to run the program where choice is the int number of map reduce task")
      }
