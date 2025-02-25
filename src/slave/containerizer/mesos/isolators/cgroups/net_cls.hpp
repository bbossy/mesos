// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __CGROUPS_NET_CLS_ISOLATOR_HPP__
#define __CGROUPS_NET_CLS_ISOLATOR_HPP__

#include <string>

#include <stout/hashmap.hpp>

#include "slave/containerizer/mesos/isolator.hpp"

namespace mesos {
namespace internal {
namespace slave {

// Uses the Linux net_cls subsystem for allocating network handles to
// containers. The network handles of a net_cls cgroup will be used for tagging
// packets originating from containers belonging to that cgroup. The tags on the
// packets can then be used by applications, such as traffic-controllers (tc)
// and firewalls (iptables), to provide network performance isolation. A more
// detailed explanation can be found at:
// https://www.kernel.org/doc/Documentation/cgroups/net_cls.txt
class CgroupsNetClsIsolatorProcess : public MesosIsolatorProcess
{
public:
  static Try<mesos::slave::Isolator*> create(const Flags& flags);

  virtual ~CgroupsNetClsIsolatorProcess();

  virtual process::Future<Nothing> recover(
      const std::list<mesos::slave::ContainerState>& states,
      const hashset<ContainerID>& orphans);

  virtual process::Future<Option<mesos::slave::ContainerLaunchInfo>> prepare(
      const ContainerID& containerId,
      const ExecutorInfo& executorInfo,
      const mesos::slave::ContainerConfig& containerConfig);

  virtual process::Future<Nothing> isolate(
      const ContainerID& containerId,
      pid_t pid);

  virtual process::Future<mesos::slave::ContainerLimitation> watch(
      const ContainerID& containerId);

  virtual process::Future<Nothing> update(
      const ContainerID& containerId,
      const Resources& resources);

  virtual process::Future<ResourceStatistics> usage(
      const ContainerID& containerId);

  virtual process::Future<Nothing> cleanup(
      const ContainerID& containerId);

private:
  CgroupsNetClsIsolatorProcess(
      const Flags& flags,
      const std::string& hierarchy);

  struct Info
  {
    Info(const std::string& _cgroup)
      : cgroup(_cgroup) {}

    const std::string cgroup;
  };

  const Flags flags;

  const std::string hierarchy;

  hashmap<ContainerID, Info> infos;
};
} // namespace slave {
} // namespace internal {
} // namespace mesos {
#endif // __CGROUPS_NET_CLS_ISOLATOR_HPP__
