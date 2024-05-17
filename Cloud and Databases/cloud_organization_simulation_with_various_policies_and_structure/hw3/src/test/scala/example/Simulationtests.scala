package example

// imports for the testing
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers

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

class Simulationtests extends AnyFlatSpec with Matchers {
  "Test1" should "Test hw3_simple VM status" in {
    val simple = hw3.hw3_simple // creating and running the object

    simple.simulate_simple()

    // getting the sizes
    val vmCreatedSize = (simple.broker0.getVmCreatedList().size())
    val vmFailedSize = simple.broker0.getVmFailedList().size()

    // asserting them to be what is expected
    (vmCreatedSize) should be(simple.VMS) // al of them were created
    (vmFailedSize) should be(0) // none failed

  }

  "Test2" should "Test hw3_simple Cloudlet states" in {
    val simple = hw3.hw3_simple // already ran it so no need to run it again

    // the number of cloudlets created
    (simple.cloudletList.size()) should be (simple.CLOUDLETS)

    // each cloudlet should be have status SUCCESS
    simple.cloudletList.forEach(e => {
      (e.getStatus()) should equal (org.cloudbus.cloudsim.cloudlets.Cloudlet.Status.SUCCESS)
      (e.isReturnedToBroker()) should be (true)

      // since this is a simple space shared env. the exec time is the
      // same as expected one
      val cputime:Int = (e.getActualCpuTime()).toInt
      val expected:Int = (simple.CLOUDLET_LENGTH/1000).toInt // converting to seconds

      (cputime) should equal (expected)
    })
  }


  "Test3" should "Test hw3_simple Hosts states" in {
    val simple = hw3.hw3_simple // already ran it so no need to run it again

    // the number of hosts
    (simple.datacentre0.size()) should equal (simple.HOSTS)

    // the scheduling interval
    (simple.datacentre0.getSchedulingInterval()) should equal (simple.INTERVAL)

    // getting all the hosts
    val hosts:List[Host] = simple.datacentre0.getHostList()

    // each host should
    hosts.forEach(e => {

      // have the expeced number of PEs
      (e.getFreePesNumber()) should equal (simple.HOST_PES)

      // not failed
      (e.isFailed()) should be (false)
    })
  }

  "Test4" should "Test hw3_simple PEs" in {
    val simple = hw3.hw3_simple // already ran it so no need to run it again

    // get the hosts
    val hosts:List[Host] = simple.datacentre0.getHostList()

    // for each host's PE
    hosts.forEach(e => {
      e.getPeList.forEach(pe => {
        (pe.getCapacity()) should equal (simple.HOST_MIPS)
      })
    })
  }


  // new
  "Test5" should "Test hw3_Random_Allocation VM status" in {
    val random_sim = hw3.hw3_Random_Allocation // creating and running the object

    random_sim.simulate_random()

    // getting the sizes
    val vmCreatedSize = (random_sim.broker0.getVmCreatedList().size())
    val vmFailedSize = random_sim.broker0.getVmFailedList().size()

    // asserting them to be what is expected
    (vmCreatedSize) should be(random_sim.VMS) // al of them were created
    (vmFailedSize) should be(0) // none failed

  }

  "Test6" should "Test hw3_Random_Allocation Cloudlet states" in {
    val random_sim = hw3.hw3_Random_Allocation // already ran it so no need to run it again

    // the number of cloudlets created
    (random_sim.cloudletList.size()) should be(random_sim.CLOUDLETS)

    // each cloudlet should be have status SUCCESS
    random_sim.cloudletList.forEach(e => {
      (e.getStatus()) should equal(org.cloudbus.cloudsim.cloudlets.Cloudlet.Status.SUCCESS)
      (e.isReturnedToBroker()) should be (true)
    })
  }


  "Test7" should "Test hw3_Random_Allocation Hosts states" in {
    val random_sim = hw3.hw3_Random_Allocation // already ran it so no need to run it again

    // the number of hosts
    (random_sim.datacentre0.size()) should equal(random_sim.HOSTS)

    // the scheduling interval
    (random_sim.datacentre0.getSchedulingInterval()) should equal(random_sim.INTERVAL)

    // getting all the hosts
    val hosts: List[Host] = random_sim.datacentre0.getHostList()

    // each host should
    hosts.forEach(e => {

      // have the expeced number of PEs
      (e.getFreePesNumber()) should equal(random_sim.HOST_PES)

      // not failed
      (e.isFailed()) should be(false)
    })
  }

  "Test8" should "Test hw3_Random_Allocation PEs" in {
    val random_sim = hw3.hw3_Random_Allocation // already ran it so no need to run it again

    // get the hosts
    val hosts: List[Host] = random_sim.datacentre0.getHostList()

    // for each host's PE
    hosts.forEach(e => {
      e.getPeList.forEach(pe => {
        (pe.getCapacity()) should equal(random_sim.HOST_MIPS)
      })
    })
  }


  //new
  "Test9" should "Test hw3_Round_Robin VM status" in {
    val rr = hw3.hw3_Round_Robin // creating and running the object

    rr.simulate_round_robin()

    // getting the sizes
    val vmCreatedSize = (rr.broker0.getVmCreatedList().size())
    val vmFailedSize = rr.broker0.getVmFailedList().size()

    // asserting them to be what is expected
    (vmCreatedSize) should be(rr.VMS) // al of them were created
    (vmFailedSize) should be(0) // none failed

  }

  "Test10" should "Test hw3_Round_Robin Cloudlet states" in {
    val rr = hw3.hw3_Round_Robin // already ran it so no need to run it again

    // the number of cloudlets created
    (rr.cloudletList.size()) should be(rr.CLOUDLETS)

    // each cloudlet should be have status SUCCESS
    rr.cloudletList.forEach(e => {
      (e.getStatus()) should equal(org.cloudbus.cloudsim.cloudlets.Cloudlet.Status.SUCCESS)
      (e.isReturnedToBroker()) should be(true)

      // since this is a rr space shared env. the exec time is the
      // same as expected one
      val cputime: Int = (e.getActualCpuTime()).toInt
      val expected: Int = (rr.CLOUDLET_LENGTH / 1000).toInt // converting to seconds

      (cputime) should equal(expected)
    })
  }


  "Test11" should "Test hw3_Round_Robin Hosts states" in {
    val rr = hw3.hw3_Round_Robin // already ran it so no need to run it again

    // the number of hosts
    (rr.datacentre0.size()) should equal(rr.HOSTS)

    // the scheduling interval
    (rr.datacentre0.getSchedulingInterval()) should equal(rr.INTERVAL)

    // getting all the hosts
    val hosts: List[Host] = rr.datacentre0.getHostList()

    // each host should
    hosts.forEach(e => {

      // have the expeced number of PEs
      (e.getFreePesNumber()) should equal(rr.HOST_PES)

      // not failed
      (e.isFailed()) should be(false)
    })
  }

  "Test12" should "Test hw3_Round_Robin PEs" in {
    val rr = hw3.hw3_Round_Robin // already ran it so no need to run it again

    // get the hosts
    val hosts: List[Host] = rr.datacentre0.getHostList()

    // for each host's PE
    hosts.forEach(e => {
      e.getPeList.forEach(pe => {
        (pe.getCapacity()) should equal(rr.HOST_MIPS)
      })
    })
  }

}
