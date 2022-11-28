package HelperUtils

import scala.collection.immutable.ListMap
import scala.util.{Failure, Success, Try}
import scala.collection.JavaConverters.*

/*
 *
 *  Copyright (c) 2021. Mark Grechanik and Lone Star Consulting, Inc. All rights reserved.
 *   
 *   Unless required by applicable law or agreed to in writing, software distributed under
 *   the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *   either express or implied.  See the License for the specific language governing permissions and limitations under the License.
 *  
 */

/*
* This module obtains configuration parameter values from application.conf and converts them
* into appropriate scala types.
* */
object Parameters2:
  private val logger = CreateLogger(classOf[Parameters2.type])
  val config = ObtainConfigReference("homework3_2") match {
    case Some(value) => value
    case None => throw new RuntimeException("Cannot obtain a reference to the config data.")
  }

  //Type match is used to dependently type configuration parameter values
  //based on the default input values of the specific config parameter.
  type ConfigType2Process[T] = T match
    case Int => Int
//    case Long => Long
    case String => String
    case Double => Double

  //It returns a function that takes the name of config entry and obtains the value of this entry if it exists
  //or it logs a warning message if it is absent and returns a default value
  private def func4Parameter[T](defaultVal: T, f: String => T): String => T =
    (pName: String) => Try(f(s"homework3_2.$pName")) match {
      case Success(value) => value
      case Failure(exception) => logger.warn(s"No config parameter $pName is provided. Defaulting to $defaultVal")
        defaultVal
    }
  end func4Parameter

  //in this dependently typed function a typesafe config API method is invoked
  //whose name and return value corresponds to the type of the type parameter, T
  private def getParam[T](pName: String, defaultVal: T): ConfigType2Process[T] =
    defaultVal match {
      case v: Int => func4Parameter(v, config.getInt)(pName)
//      case v: Long => func4Parameter(v, config.getLong)(pName)
      case v: String => func4Parameter(v, config.getString)(pName)
      case v: Double => func4Parameter(v, config.getDouble)(pName)
    }
  end getParam

  val HOSTS = getParam("HOSTS", 1)
  val HOST_PES = getParam("HOST_PES", 10)
  val HOST_MIPS = getParam("HOST_MIPS", 2000)
  val HOST_RAM = getParam("HOST_RAM", 16384) //in Megabytes
  val HOST_BW = getParam("HOST_BW", 16384) //in Megabits/s
  val HOST_STORAGE = getParam("HOST_STORAGE", 1_000_000)

  val VMS = getParam("VMS", 5)
  val VM_PES = getParam("VM_PES", 4)
  val VM_MIPS = getParam("VM_MIPS", 1000)
  val VM_RAM = getParam("VM_RAM", 2048)
  val VM_BW = getParam("VM_BW", 2048)
  val VM_SIZE = getParam("VM_SIZE", 10_000)
  val VM_SCALING_FACTOR = getParam("VM_SCALING_FACTOR", 0.1)
  val VM_SCALING_LOWER_THRESHOLD = getParam("VM_SCALING_LOWER_THRESHOLD", 0.35)
  val VM_SCALING_UPPER_THRESHOLD = getParam("VM_SCALING_UPPER_THRESHOLD", 0.9)

  val CLOUDLETS = getParam("CLOUDLETS", 10)
  val CLOUDLET_PES = getParam("CLOUDLET_PES", 2)
  val CLOUDLET_LENGTH = getParam("CLOUDLET_LENGTH", 10_000)
  val CLOUDLET_SIZE = getParam("CLOUDLET_SIZE", 512)

  val CLOUDLET_DYNAMIC_USAGE = getParam("CLOUDLET_DYNAMIC_USAGE", 0.5)

  val INTERVAL = getParam("INTERVAL", 0.5)