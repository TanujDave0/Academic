package hw3

import HelperUtils.{CreateLogger, Parameters3}

import org.cloudsimplus.autoscaling.VerticalVmScaling
import org.cloudsimplus.autoscaling.VerticalVmScalingSimple
import org.cloudbus.cloudsim.resources.Processor
import org.cloudbus.cloudsim.allocationpolicies.VmAllocationPolicy
import org.cloudbus.cloudsim.allocationpolicies.VmAllocationPolicyRoundRobin
import org.cloudbus.cloudsim.allocationpolicies.VmAllocationPolicySimple
import org.cloudbus.cloudsim.brokers.DatacenterBroker
import org.cloudbus.cloudsim.brokers.DatacenterBrokerSimple
import org.cloudbus.cloudsim.cloudlets.Cloudlet
import org.cloudbus.cloudsim.cloudlets.CloudletSimple
import org.cloudbus.cloudsim.core.CloudSim
import org.cloudbus.cloudsim.datacenters.Datacenter
import org.cloudbus.cloudsim.datacenters.DatacenterSimple
import org.cloudbus.cloudsim.distributions.ContinuousDistribution
import org.cloudbus.cloudsim.distributions.UniformDistr
import org.cloudbus.cloudsim.hosts.Host
import org.cloudbus.cloudsim.hosts.HostSimple
import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple
import org.cloudbus.cloudsim.provisioners.ResourceProvisionerSimple
import org.cloudbus.cloudsim.resources.Pe
import org.cloudbus.cloudsim.resources.PeSimple
import org.cloudbus.cloudsim.schedulers.cloudlet.CloudletSchedulerTimeShared
import org.cloudbus.cloudsim.schedulers.cloudlet.CloudletSchedulerSpaceShared
import org.cloudbus.cloudsim.schedulers.vm.VmSchedulerTimeShared
import org.cloudbus.cloudsim.util.TimeUtil
import org.cloudbus.cloudsim.utilizationmodels.UtilizationModel
import org.cloudbus.cloudsim.utilizationmodels.UtilizationModelDynamic
import org.cloudbus.cloudsim.utilizationmodels.UtilizationModelFull
import org.cloudbus.cloudsim.vms.Vm
import org.cloudbus.cloudsim.vms.VmSimple
import org.cloudsimplus.builders.tables.CloudletsTableBuilder
import org.cloudsimplus.util.Log
import java.util.*


object hw3_Random_Allocation:
  // importing all parameters for our simulation from our conf file
  import HelperUtils.Parameters3.*
  private val logger = CreateLogger(classOf[hw3_Random_Allocation.type]) // creating a logger for it

  // getting all the variables from the conf for this simulation

  // for hosts
  val HOSTS = Parameters3.HOSTS
  val HOST_PES = Parameters3.HOST_PES
  val HOST_MIPS = Parameters3.HOST_MIPS
  val HOST_RAM = Parameters3.HOST_RAM
  val HOST_BW = Parameters3.HOST_BW
  val HOST_STORAGE = Parameters3.HOST_STORAGE

  // for VMs
  val VMS = Parameters3.VMS
  val VM_PES = Parameters3.VM_PES
  val VM_MIPS = Parameters3.VM_MIPS
  val VM_RAM = Parameters3.VM_RAM
  val VM_BW = Parameters3.VM_BW
  val VM_SIZE = Parameters3.VM_SIZE
  val VM_SCALING_FACTOR = Parameters3.VM_SCALING_FACTOR
  val VM_SCALING_UPPER_THRESHOLD = Parameters3.VM_SCALING_UPPER_THRESHOLD
  val VM_SCALING_LOWER_THRESHOLD = Parameters3.VM_SCALING_LOWER_THRESHOLD

  // for Cloudlets
  val CLOUDLETS = Parameters3.CLOUDLETS
  val CLOUDLET_PES = Parameters3.CLOUDLET_PES
  val CLOUDLET_LENGTH = Parameters3.CLOUDLET_LENGTH
  val CLOUDLET_SIZE = Parameters3.CLOUDLET_SIZE
  val CLOUDLET_DYNAMIC_USAGE = Parameters3.CLOUDLET_DYNAMIC_USAGE

  val INTERVAL = Parameters3.INTERVAL

  // a stream of random doubles from [0, 1)
  // used for the random VM allocation policy
  // a random double generator
  final val random = Random()

  // creating a simulation, setting it to final
  final val simulation = new CloudSim()

  val datacentre0 = createDatacenterRandomPolicy()

  val broker0 = new DatacenterBrokerSimple(simulation)

//  val vmList = createVms()
      val vmList = createVerticleScalingVms()
  val cloudletList = createCloudlets()

  // defining all the functions to be used

  // create a simple host
  def createHost(): Host = {
    // create a list of PEs (computing units/processors)
    val peList: java.util.List[Pe] = new java.util.ArrayList[Pe]

    // add HOSTS_PES number of simple PEs per host
    (1 to HOST_PES).toList.foreach(e => peList.add(new PeSimple(HOST_MIPS)))

    // create a simple host with
    // HOST_RAM ram
    // HOST_BW bandwidth
    // HOST_STORAGE storage
    // and the peList created
    val host = new HostSimple(HOST_RAM.toLong, HOST_BW.toLong, HOST_STORAGE.toLong, peList)

    // setting the scheduler to a time shared policy
    host.setVmScheduler(new VmSchedulerTimeShared())

    // return it
    host
  }

  // creates a simple datacenter with HOSTS number of hosts
  // uses the custom first available suitable Host as the allocaiton policy
  // returns the datacenter
  def createDatacenterFirstHost(): Datacenter = {
    // creates a list of hosts
    val hostlist: java.util.List[Host] = java.util.ArrayList[Host]

    // add HOSTS number of elements into the host list
    (1 to HOSTS).toList.foreach(e => hostlist.add(createHost()))

    // adding a custom VM allocation policy of first avaiable Host allocation
    val vmPolicy = new VmAllocationPolicySimple() // creating a simple policy

    // replacing the simple policy mehtod with our first available Host allocation
    vmPolicy.setFindHostForVmFunction(allocateToFirstHostAvailable)

    // setting the ROUND ROBIN Policy as the vm allocation policy and returning the datacenter
    val d = DatacenterSimple(simulation, hostlist, vmPolicy)
    d.setSchedulingInterval(INTERVAL)
    d
  }

  // creates a datacenter with HOSTS number of hosts
  // uses Round Robin policy as the allocaiton policy
  // returns the datacenter
  def createDatacenterRoundRobin(): Datacenter = {
    // creates a list of hosts
    val hostlist: java.util.List[Host] = java.util.ArrayList[Host]

    // add HOSTS number of elements into the host list
    (1 to HOSTS).toList.foreach(e => hostlist.add(createHost()))

    // setting the ROUND ROBIN Policy as the vm allocation policy and returning the datacenter
    val d = DatacenterSimple(simulation, hostlist, VmAllocationPolicyRoundRobin())
    d.setSchedulingInterval(INTERVAL)
    d
  }

  // creates a simple datacenter with HOSTS number of hosts
  // uses the random assignment for suitable Host as the allocaiton policy
  // returns the datacenter
  def createDatacenterRandomPolicy(): Datacenter = {
    // creates a list of hosts
    val hostlist: java.util.List[Host] = java.util.ArrayList[Host]

    // add HOSTS number of elements into the host list
    (1 to HOSTS).toList.foreach(e => hostlist.add(createHost()))

    // adding a custom VM allocation policy of first avaiable Host allocation
    val vmPolicy = new VmAllocationPolicySimple() // creating a simple policy

    // replacing the simple policy mehtod with our first available Host allocation
    vmPolicy.setFindHostForVmFunction(allocateToARaondomHost)

    // setting the ROUND ROBIN Policy as the vm allocation policy and returning the datacenter
    val d = DatacenterSimple(simulation, hostlist, vmPolicy)
    d.setSchedulingInterval(INTERVAL)
    d
  }

  // one of the VM allocation policies
  // a naive strategy to just allocate to the first Host that can occupy the VM
  def allocateToFirstHostAvailable(vmPolicy: VmAllocationPolicy, currVm: Vm): Optional[Host] = {
    val hostList: java.util.List[Host] = vmPolicy.getHostList() // get the host list

    // for each host check the compatibility
    hostList.forEach(e => {
      if (e.isSuitableForVm(currVm)) return Optional.of(e)
    })

    // couldnt find a suitable host
    Optional.empty()
  }

  // one of the VM allocation policies
  // a naive strategy to just allocate to a random Host that can occupy the VM
  def allocateToARaondomHost(vmPolicy: VmAllocationPolicy, currVm: Vm): Optional[Host] = {
    val hostList: java.util.List[Host] = vmPolicy.getHostList() // get the host list

    // for each host check the compatibility
    hostList.forEach(e => {
      // finding the a random host using the random double [0, 1)
      // and the list of hosts
      val pos:Int = (random.nextDouble() * hostList.size()).toInt
      logger.info(f"generated $pos")

      // check if the host at the random position is suitable
      if (hostList.get(pos).isSuitableForVm(currVm)) return Optional.of(hostList.get(pos))
    })

    // couldnt find a suitable host
    Optional.empty()
  }

  // creates a list of simple VMs
  def createVms(): java.util.List[Vm] = {
    val vmList: java.util.List[Vm] = new java.util.ArrayList[Vm]

    // add VMS number of VMs to the list
    (1 to VMS).toList.foreach(e => {val temp2 = new VmSimple(VM_MIPS, VM_PES)
                      temp2.setRam(VM_RAM) // the ram size
                      temp2.setBw(VM_BW) // bandwidth
                      temp2.setSize(VM_SIZE) // size
                      // the type of cloudlet scheduler, currently space shared, thus creates a queue of cloudlets if
                      // the processing capacity is full and goes through the queue
//                      temp2.setCloudletScheduler(new CloudletSchedulerTimeShared())
                      temp2.setCloudletScheduler(new CloudletSchedulerSpaceShared())
                      vmList.add(temp2)}) // add it to the list

    vmList // return
  }

  // creates a list of vertically scalable VMs
  // these VMs can dynamically increase/decrease their number of PEs
  // maintaining a range of Host PE usage threashold
  // thus the number of cloudlets that can be processed will increase or decrease
  // automatically as per the incoming requests
  def createVerticleScalingVms(): java.util.List[Vm] = {
    val vmList: java.util.List[Vm] = new java.util.ArrayList[Vm]

    // add VMS number of VMs to the list
    (1 to VMS).toList.foreach(e => {
      val temp2 = new VmSimple(VM_MIPS, VM_PES)
      temp2.setRam(VM_RAM) // the ram size
      temp2.setBw(VM_BW) // bandwidth
      temp2.setSize(VM_SIZE) // size
      // the type of cloudlet scheduler, currently space shared, thus creates a queue of cloudlets if
      // the processing capacity is full and goes through the queue
//      temp2.setCloudletScheduler(CloudletSchedulerSpaceShared())
      temp2.setPeVerticalScaling(peScaling())
      vmList.add(temp2)
    }) // add it to the list

    vmList // return
  }

  // vertical scaling policy for the VMs
  // increases or decreases the number of PEs
  def peScaling(): VerticalVmScaling = {
    val scalingPolicy = VerticalVmScalingSimple(classOf[Processor], VM_SCALING_FACTOR)

    scalingPolicy.setResourceScaling((vs) => vs.getScalingFactor() * vs.getAllocatedResource())

    // setting the upper thereshold to trigger the scaling
    scalingPolicy.setUpperThresholdFunction(upperThreshold)

    // setting the lower thereshold to trigger the scaling
    scalingPolicy.setUpperThresholdFunction(lowerThreshold)

    scalingPolicy
  }

  // resorce scaling
//  def resourceScaling(v: Vm): Double = VM_SCALING_FACTOR * v.getAllocatedResources()

  // function for getting the lower threshold
  def lowerThreshold(v: Vm): Double = VM_SCALING_LOWER_THRESHOLD

  // function for getting the upper threshold
  def upperThreshold(v: Vm): Double = VM_SCALING_UPPER_THRESHOLD

  def createCloudlets(): java.util.List[Cloudlet] = {
    val cloudletList: java.util.List[Cloudlet] = new java.util.ArrayList[Cloudlet]

    val utilizationModel = new UtilizationModelDynamic(CLOUDLET_DYNAMIC_USAGE)

    (1 to CLOUDLETS).toList.foreach(e => {val temp2 = new CloudletSimple(CLOUDLET_LENGTH, CLOUDLET_PES, utilizationModel)
                      temp2.setUtilizationModelBw(utilizationModel)
                      temp2.setUtilizationModelRam(utilizationModel)
                      temp2.setUtilizationModelCpu(new UtilizationModelFull())
                      temp2.setSizes(CLOUDLET_SIZE)
                      cloudletList.add(temp2)})

    cloudletList
  }

  @main def hw3_RandomAllocation_main() = {simulate_random()}

  def simulate_random() = {
    Log.setLevel(ch.qos.logback.classic.Level.ALL)

    logger.info("Welcome to the cloud simulations")

    logger.info("creating a simulation")

    logger.info("creating datacentre 0")

    broker0.submitVmList(vmList)
    broker0.submitCloudletList(cloudletList)

    logger.info("Starting simulation")

    simulation.start()

    val f = broker0.getCloudletFinishedList()
    val b = CloudletsTableBuilder(f)

    logger.info("displaying the stats")

    b.build()
  }
