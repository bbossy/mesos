---
layout: documentation
---


# Mesos Configuration

The Mesos master and slave can take a variety of configuration options
through command-line arguments, or environment variables. A list of
the available options can be seen by running `mesos-master --help` or
`mesos-slave --help`. Each option can be set in two ways:

* By passing it to the binary using `--option_name=value`, either
specifying the value directly, or specifying a file in which the value
resides (`--option_name=file://path/to/file`). The path can be
absolute or relative to the current working directory.

* By setting the environment variable `MESOS_OPTION_NAME` (the option
name with a `MESOS_` prefix added to it).

Configuration values are searched for first in the environment, then
on the command-line.

**Important Options**

If you have special compilation requirements, please refer to
`./configure --help` when configuring Mesos. Additionally, this
documentation lists only a recent snapshot of the options in Mesos. A
definitive source for which flags your version of Mesos supports can
be found by running the binary with the flag `--help`, for example
`mesos-master --help`.

## Master and Slave Options

*These options can be supplied to both masters and slaves.*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>

  <tr>
    <td>
      --advertise_ip=VALUE
    </td>
    <td>
      IP address advertised to reach mesos master/slave. Mesos master/slave
      does not bind using this IP address. However, this IP address may be
      used to access Mesos master/slave.
    </td>
  </tr>
  <tr>
    <td>
      --advertise_port=VALUE
    </td>
    <td>
      Port advertised to reach mesos master/slave (along with
      <code>advertise_ip</code>). Mesos master/slave does not bind using this
      port. However, this port (along with <code>advertise_ip</code>) may be
      used to access Mesos master/slave.
    </td>
  </tr>
  <tr>
    <td>
      --external_log_file=VALUE
    </td>
    <td>
      Specify the externally managed log file. This file will be
      exposed in the webui and HTTP API. This is useful when using
      stderr logging as the log file is otherwise unknown to Mesos.
    </td>
  </tr>
  <tr>
    <td>
      --firewall_rules=VALUE
    </td>
    <td>
      The value could be a JSON-formatted string of rules or a file path
      containing the JSON-formatted rules used in the endpoints firewall. Path
      could be of the form <code>file:///path/to/file</code> or
      <code>/path/to/file</code>.
      <p/>
      See the <code>Firewall</code> message in <code>flags.proto</code>
      for the expected format.
      <p/>
      Example:
<pre><code>{
  "disabled_endpoints" : {
    "paths" : [
      "/files/browse",
      "/slave(0)/stats.json"
    ]
  }
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --[no-]help
    </td>
    <td>
      Prints this help message. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]initialize_driver_logging
    </td>
    <td>
      Whether to automatically initialize Google logging of scheduler
      and/or executor drivers. (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --ip=VALUE
    </td>
    <td>
      IP address to listen on; this cannot be used in conjunction
      with <code>--ip_discovery_command</code>.
    </td>
  </tr>
  <tr>
    <td>
      --ip_discovery_command=VALUE
    </td>
    <td>
      Optional IP discovery command: if set, it is expected to emit
      the IP address which Master will try to bind to.  Cannot be used
      in conjunction with <code>--ip</code>.
    </td>
  </tr>
  <tr>
    <td>
      --log_dir=VALUE
    </td>
    <td>
      Location to put log files. (no default, nothing is written to disk unless
      specified; does not affect logging to stderr)
    </td>
  </tr>
  <tr>
    <td>
      --logbufsecs=VALUE
    </td>
    <td>
      How many seconds to buffer log messages for. (default: 0)
    </td>
  </tr>
  <tr>
    <td>
      --logging_level=VALUE
    </td>
    <td>
      Log message at or above this level. Possible values: <code>INFO</code>,
      <code>WARNING</code>, <code>ERROR</code>; if quiet flag is used, this will
      affect just the logs from <code>log_dir</code>, if specified.
      (default: INFO)
    </td>
  </tr>
  <tr>
    <td>
      --port=VALUE
    </td>
    <td>
      Port to listen on. (master default: 5050; slave default: 5051)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]quiet
    </td>
    <td>
      Disable logging to stderr. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]version
    </td>
    <td>
      Show version and exit. (default: false)
    </td>
  </tr>
</table>

## Master Options

*Required Flags*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --quorum=VALUE
    </td>
    <td>
      The size of the quorum of replicas when using
      <code>replicated_log</code>-based
      registry. It is imperative to set this value to be a majority of
      masters i.e., quorum > (number of masters)/2.
      <p/>

      <b>NOTE</b> Not required if master is run in standalone mode (non-HA).
    </td>
  </tr>
  <tr>
    <td>
      --work_dir=VALUE
    </td>
    <td>
      Where to store the persistent information stored in the Registry.
    </td>
  </tr>
  <tr>
    <td>
      --zk=VALUE
    </td>
    <td>
      ZooKeeper URL (used for leader election amongst masters)
      May be one of:
<pre><code>zk://host1:port1,host2:port2,.../path
zk://username:password@host1:port1,host2:port2,.../path
file:///path/to/file (where file contains one of the above)</code></pre>
      <p/>
      <b>NOTE</b> Not required if master is run in standalone mode (non-HA).
    </td>
  </tr>
</table>

*Optional Flags*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --acls=VALUE
    </td>
    <td>
      Specify the ACLs used for framework/operator authentication and
      authorization. The value is a JSON-formatted string of ACLs. Remember you
      can also use the <code>file:///path/to/file</code> or
      <code>/path/to/file</code> argument value format to read the JSON from a
      file.
      <p/>
      See the ACLs protobuf in authorizer.proto for the expected format.
      <p/>
      JSON file example:
<pre><code>{
  "register_frameworks": [
    {
      "principals": { "type": "ANY" },
      "roles": { "values": ["a"] }
    }
  ],
  "run_tasks": [
    {
      "principals": { "values": ["a", "b"] },
      "users": { "values": ["c"] }
    }
  ],
  "teardown_frameworks": [
    {
      "principals": { "values": ["a", "b"] },
      "framework_principals": { "values": ["c"] }
    }
  ]
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --allocation_interval=VALUE
    </td>
    <td>
      Amount of time to wait between performing
      (batch) allocations (e.g., 500ms, 1sec, etc). (default: 1secs)
    </td>
  </tr>
  <tr>
    <td>
      --allocator=VALUE
    </td>
    <td>
      Allocator to use for resource allocation to frameworks.
      Use the default <code>HierarchicalDRF</code> allocator, or load
      an alternate allocator module using <code>--modules</code>.
      (default: HierarchicalDRF)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]authenticate
    </td>
    <td>
      If <code>authenticate</code> is <code>true</code> only authenticated
      frameworks are allowed to register. If <code>false</code> unauthenticated
      frameworks are also allowed to register. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]authenticate_slaves
    </td>
    <td>
      If <code>true</code> only authenticated slaves are allowed to register.
      <p/>
      If <code>false</code> unauthenticated slaves are also allowed to register.
      (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]authenticate_http
    </td>
    <td>
      If <code>true</code> only authenticated requests for HTTP endpoints
      supporting authentication are allowed.
      <p/>
      If <code>false</code> unauthenticated HTTP endpoint requests are also allowed.
      (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --authenticators=VALUE
    </td>
    <td>
      Authenticator implementation to use when authenticating frameworks
      and/or slaves. Use the default <code>crammd5</code>, or
      load an alternate authenticator module using <code>--modules</code>.
      (default: crammd5)
    </td>
  </tr>
  <tr>
    <td>
      --http_authenticators=VALUE
    </td>
    <td>
      HTTP authenticator implementation to use when handling requests to
      authenticated endpoints. Use the default <code>basic<code>, or
      load an alternate HTTP authenticator module using <code>--modules</code>.
      <p/>
      Currently there is no support for multiple HTTP authenticators.
      (default: basic)
    </td>
  </tr>
  <tr>
    <td>
      --authorizers=VALUE
    </td>
    <td>
      Authorizer implementation to use when authorizating actions that
      required it. Use the default <code>local</code>, or load an alternate
      authorizer module using <code>--modules</code>.
      <br/>
      Note that if the flag <code>--authorizers</code> is provided with a
      value different than the default <code>local</code>, the ACLs passed
      through the <code>--acls</code> flag will be ignored.
      <br/>
      Currently there's no support for multiple authorizers.
      (default: local)
    </td>
  </tr>
  <tr>
    <td>
      --cluster=VALUE
    </td>
    <td>
      Human readable name for the cluster, displayed in the webui.
    </td>
  </tr>
  <tr>
    <td>
      --credentials=VALUE
    </td>
    <td>
      Either a path to a text file with a list of credentials,
      each line containing <code>principal</code> and <code>secret</code>
      separated by whitespace, or a path to a JSON-formatted file containing
      credentials. Path should be of the form <code>file:///path/to/file</code>
      or <code>/path/to/file</code>.
      <p/>
      JSON file Example:
<pre><code>{
  "credentials": [
    {
      "principal": "sherman",
      "secret": "kitesurf"
    }
  ]
}</code></pre>

      <p/>
      Text file Example:
<pre><code>    username secret </code></pre>

    </td>
  </tr>
  <tr>
    <td>
      --framework_sorter=VALUE
    </td>
    <td>
      Policy to use for allocating resources between a given user's frameworks.
      Options are the same as for user_allocator. (default: drf)
    </td>
  </tr>
  <tr>
    <td>
      --hooks=VALUE
    </td>
    <td>
      A comma-separated list of hook modules to be installed inside master.
    </td>
  </tr>
  <tr>
    <td>
      --hostname=VALUE
    </td>
    <td>
      The hostname the master should advertise in ZooKeeper.<br>
      If left unset, the hostname is resolved from the IP address that the slave
      binds to; unless the user explicitly prevents that, using
      <code>--no-hostname_lookup</code>, in which case the IP itself is used.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]hostname_lookup
    </td>
    <td>
      Whether we should execute a lookup to find out the server's hostname, if
      not explicitly set (via, e.g., <code>--hostname</code>). If set to
      <code>false</code> it will cause Mesos to use the IP address, unless the
      hostname is explicitly set. (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]log_auto_initialize
    </td>
    <td>
      Whether to automatically initialize the replicated log used for the
      registry. If this is set to false, the log has to be manually initialized
      when used for the very first time. (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --max_completed_frameworks=VALUE
    </td>
    <td>
      Maximum number of completed frameworks to store in memory. (default: 50)
    </td>
  </tr>
  <tr>
    <td>
      --max_completed_tasks_per_framework=VALUE
    </td>
    <td>
      Maximum number of completed tasks per framework to store in memory.
      (default: 1000)
    </td>
  </tr>
  <tr>
    <td>
      --max_slave_ping_timeouts=VALUE
    </td>
    <td>
      The number of times a slave can fail to respond to a ping from the master.
      Slaves that incur more than <code>max_slave_ping_timeouts</code> timeouts
      will be removed. (default: 5)
    </td>
  </tr>
  <tr>
    <td>
      --modules=VALUE
    </td>
    <td>
      List of modules to be loaded and be available to the internal subsystems.
      <p/>
      Use <code>--modules=filepath</code> to specify the list of modules via a
      file containing a JSON-formatted string.
      Remember you can also use the <code>file:///path/to/file</code> or
      <code>/path/to/file</code> argument value format to write the JSON in a
      file.<p/>
      Use <code>--modules="{...}"</code> to specify the list of modules inline.
      <p/>
      JSON file example:
<pre><code>{
  "libraries": [
    {
      "file": "/path/to/libfoo.so",
      "modules": [
        {
          "name": "org_apache_mesos_bar",
          "parameters": [
            {
              "key": "X",
              "value": "Y"
            }
          ]
        },
        {
          "name": "org_apache_mesos_baz"
        }
      ]
    },
    {
      "name": "qux",
      "modules": [
        {
          "name": "org_apache_mesos_norf"
        }
      ]
    }
  ]
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --offer_timeout=VALUE
    </td>
    <td>
      Duration of time before an offer is rescinded from a framework.
      <p/>
      This helps fairness when running frameworks that hold on to offers,
      or frameworks that accidentally drop offers.
    </td>
  </tr>
  <tr>
    <td>
      --rate_limits=VALUE
    </td>
    <td>
      The value could be a JSON-formatted string of rate limits
      or a file path containing the JSON-formatted rate limits used
      for framework rate limiting.
      <p/>
      Remember you can also use the <code>file:///path/to/file</code> or
      <code>/path/to/file</code> argument value format to read the JSON from a
      file.
      <p/>

      See the RateLimits protobuf in mesos.proto for the expected format.
      <p/>

      Example:
<pre><code>{
  "limits": [
    {
      "principal": "foo",
      "qps": 55.5
    },
    {
      "principal": "bar"
    }
  ],
  "aggregate_default_qps": 33.3
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --recovery_slave_removal_limit=VALUE
    </td>
    <td>
      For failovers, limit on the percentage of slaves that can be removed
      from the registry *and* shutdown after the re-registration timeout
      elapses. If the limit is exceeded, the master will fail over rather
      than remove the slaves.
      <p/>
      This can be used to provide safety guarantees for production
      environments. Production environments may expect that across Master
      failovers, at most a certain percentage of slaves will fail
      permanently (e.g., due to rack-level failures).
      <p/>
      Setting this limit would ensure that a human needs to get
      involved should an unexpected widespread failure of slaves occur
      in the cluster.
      <p/>
      Values: [0%-100%] (default: 100%)
    </td>
  </tr>
  <tr>
    <td>
      --registry=VALUE
    </td>
    <td>
      Persistence strategy for the registry.
      <p/>
      Available options are <code>replicated_log</code>, <code>in_memory</code>
      (for testing). (default: replicated_log)
    </td>
  </tr>
  <tr>
    <td>
      --registry_fetch_timeout=VALUE
    </td>
    <td>
      Duration of time to wait in order to fetch data from the registry after
      which the operation is considered a failure. (default: 1mins)
    </td>
  </tr>
  <tr>
    <td>
      --registry_store_timeout=VALUE
    </td>
    <td>
      Duration of time to wait in order to store data in the registry after
      which the operation is considered a failure. (default: 5secs)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]registry_strict
    </td>
    <td>
      Whether the Master will take actions based on the persistent
      information stored in the Registry. Setting this to false means
      that the Registrar will never reject the admission, readmission,
      or removal of a slave. Consequently, <code>false</code> can be used to
      bootstrap the persistent state on a running cluster.
      <p/>
      NOTE: This flag is *experimental* and should not be used in
      production yet. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --roles=VALUE
    </td>
    <td>
      A comma-separated list of the allocation roles that frameworks
      in this cluster may belong to. This flag is deprecated;
      if it is not specified, any role name can be used.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]root_submissions
    </td>
    <td>
      Can root submit frameworks? (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --slave_ping_timeout=VALUE
    </td>
    <td>
      The timeout within which each slave is expected to respond to a
      ping from the master. Slaves that do not respond within
      <code>max_slave_ping_timeouts</code> ping retries will be removed.
      (default: 15secs)
    </td>
  </tr>
  <tr>
    <td>
      --slave_removal_rate_limit=VALUE
    </td>
    <td>
      The maximum rate (e.g., <code>1/10mins</code>, <code>2/3hrs</code>, etc)
      at which slaves will be removed from the master when they fail health
      checks. By default slaves will be removed as soon as they fail the health
      checks.
      <p/>
      The value is of the form
      <code>Number of slaves</code>/<code>Duration</code>.
    </td>
  </tr>
  <tr>
    <td>
      --slave_reregister_timeout=VALUE
    </td>
    <td>
      The timeout within which all slaves are expected to re-register
      when a new master is elected as the leader. Slaves that do not
      re-register within the timeout will be removed from the registry
      and will be shutdown if they attempt to communicate with master.
      <p/>
      NOTE: This value has to be at least 10mins. (default: 10mins)
    </td>
  </tr>
  <tr>
    <td>
      --user_sorter=VALUE
    </td>
    <td>
      Policy to use for allocating resources between users. May be one of:
      <p/>
      dominant_resource_fairness (drf) (default: drf)
    </td>
  </tr>
  <tr>
    <td>
      --webui_dir=VALUE
    </td>
    <td>
      Directory path of the webui files/assets.
      (default: /usr/local/share/mesos/webui)
    </td>
  </tr>
  <tr>
    <td>
      --weights=VALUE
    </td>
    <td>
      A comma-separated list of role/weight pairs of the form
      <code>role=weight,role=weight</code>. Weights are used
      to indicate forms of priority.
    </td>
  </tr>
  <tr>
    <td>
      --whitelist=VALUE
    </td>
    <td>
      A filename which contains a list of slaves (one per line) to advertise
      offers for. The file is watched, and periodically re-read to refresh
      the slave whitelist. By default there is no whitelist / all machines are
      accepted. (default: None)
     <p/>

      Example:
      <pre><code>file:///etc/mesos/slave_whitelist</code></pre>
      <p/>
    </td>
  </tr>
  <tr>
    <td>
      --zk_session_timeout=VALUE
    </td>
    <td>
      ZooKeeper session timeout. (default: 10secs)
    </td>
  </tr>
</table>

*Flags available when configured with `--with-network-isolator`*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
  <tr>
    <td>
      --max_executors_per_slave=VALUE
    </td>
    <td>
      Maximum number of executors allowed per slave. The network
      monitoring/isolation technique imposes an implicit resource
      acquisition on each executor (# ephemeral ports), as a result
      one can only run a certain number of executors on each slave.
      <p/>
      This flag was added as a hack to avoid frameworks getting offers
      when we have allocated all of the ephemeral port range on the slave.
    </td>
  </tr>
</table>

## Slave Options

*Required Flags*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --master=VALUE
    </td>
    <td>
      This specifies how to connect to a master or a quorum of masters. This flag works with 3 different techniques. It may be one of:
      <ol>
        <li> hostname or ip to a master, e.g.,
<pre><code>--master=localhost:5050
--master=10.0.0.5:5050
</code></pre>
        </li>

        <li> zookeeper or quorum hostname/ip + port + master registration path </li>
<pre><code>--master=zk://host1:port1,host2:port2,.../path
--master=zk://username:password@host1:port1,host2:port2,.../path
</code></pre>
        </li>

        <li> a path to a file containing either one of the above options. You
        can also use the <code>file:///path/to/file</code> syntax to read the
        argument from a file which contains one of the above.
        </li>
      </ol>
    </td>
  </tr>
</table>

*Optional Flags*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --attributes=VALUE
    </td>
    <td>
      Attributes of machine, in the form:
      <p/>
      <code>rack:2</code> or <code>'rack:2;u:1'</code>
    </td>
  </tr>
  <tr>
    <td>
      --authenticatee=VALUE
    </td>
    <td>
      Authenticatee implementation to use when authenticating against the
      master. Use the default <code>crammd5</code>, or
      load an alternate authenticatee module using <code>--modules</code>.
      (default: crammd5)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]cgroups_cpu_enable_pids_and_tids_count
    </td>
    <td>
      Cgroups feature flag to enable counting of processes and threads
      inside a container. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]cgroups_enable_cfs
    </td>
    <td>
      Cgroups feature flag to enable hard limits on CPU resources
      via the CFS bandwidth limiting subfeature.
      (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --cgroups_hierarchy=VALUE
    </td>
    <td>
      The path to the cgroups hierarchy root.
      (default: /sys/fs/cgroup)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]cgroups_limit_swap
    </td>
    <td>
      Cgroups feature flag to enable memory limits on both memory and
      swap instead of just memory.
      (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --cgroups_root=VALUE
    </td>
    <td>
      Name of the root cgroup.
      (default: mesos)
    </td>
  </tr>
  <tr>
    <td>
      --systemd_runtime_directory=VALUE
    </td>
    <td>
      The path to the systemd system run time directory.
      (default: /run/systemd/system)
    </td>
  </tr>
  <tr>
    <td>
      --container_disk_watch_interval=VALUE
    </td>
    <td>
      The interval between disk quota checks for containers. This flag is
      used for the <code>posix/disk</code> isolator. (default: 15secs)
    </td>
  </tr>
  <tr>
    <td>
      --containerizer_path=VALUE
    </td>
    <td>
      The path to the external containerizer executable used when
      external isolation is activated (<code>--isolation=external</code>).
    </td>
  </tr>
  <tr>
    <td>
      --containerizers=VALUE
    </td>
    <td>
      Comma-separated list of containerizer implementations
      to compose in order to provide containerization.
      <p/>
      Available options are 'mesos', 'external', and
      'docker' (on Linux). The order the containerizers
      are specified is the order they are tried
      (<code>--containerizers=mesos</code>).
      (default: mesos)
    </td>
  </tr>
  <tr>
    <td>
      --credential=VALUE
    </td>
    <td>
      A path to a text file with a single line
      containing 'principal' and 'secret' separated by whitespace.

      <p/>
      Or a path containing the JSON-formatted information used for one credential.
      <p/>
      Path should be of the form <code>file://path/to/file</code>.
      <p/>
      Remember you can also use
      the <code>file:///path/to/file</code> argument value format to read the
      value from a file.
      </p>
      JSON file example:
<pre><code>{
  "principal": "username",
  "secret": "secret"
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --default_container_image=VALUE
    </td>
    <td>
      The default container image to use if not specified by a task,
      when using external containerizer.
    </td>
  </tr>
  <tr>
    <td>
      --default_container_info=VALUE
    </td>
    <td>
      JSON-formatted ContainerInfo that will be included into
      any ExecutorInfo that does not specify a ContainerInfo.
      <p/>
      See the ContainerInfo protobuf in mesos.proto for
      the expected format.
      <p/>
      Example:
<pre><code>{
  "type": "MESOS",
  "volumes": [
    {
      "host_path": "./.private/tmp",
      "container_path": "/tmp",
      "mode": "RW"
    }
  ]
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --default_role=VALUE
    </td>
    <td>
      Any resources in the --resources flag that
      omit a role, as well as any resources that
      are not present in --resources but that are
      automatically detected, will be assigned to
      this role. (default: *)
    </td>
  </tr>
  <tr>
    <td>
      --disk_watch_interval=VALUE
    </td>
    <td>
      Periodic time interval (e.g., 10secs, 2mins, etc)
      to check the disk usage. (default: 1mins)
    </td>
  </tr>
  <tr>
    <td>
      --docker=VALUE
    </td>
    <td>
      The absolute path to the docker executable for docker
      containerizer.
      (default: docker)
    </td>
  </tr>
  <tr>
    <td>
      --docker_auth_server=VALUE
    </td>
    <td>
      Docker authentication server used to authenticate with Docker registry.
      (default: https://auth.docker.io)
    </td>
  </tr>
  <tr>
    <td>
      --docker_local_archives_dir=VALUE
    </td>
    <td>
      Directory for docker local puller to look in for image archives.
      (default: /tmp/mesos/images/docker)
    </td>
  </tr>
  <tr>
    <td>
      --docker_puller=VALUE
    </td>
    <td>
      Strategy for docker puller to fetch images.
      (default: local)
    </td>
  </tr>
  <tr>
    <td>
      --docker_puller_timeout_secs=VALUE
    </td>
    <td>
      Timeout in seconds for pulling images from the Docker registry.
      (default: 60)
    </td>
  </tr>
  <tr>
    <td>
      --docker_registry=VALUE
    </td>
    <td>
      The default url for pulling Docker images. It could either be a Docker
      registry server url (i.e: https://registry.docker.io), or a local path
      (i.e: file:///tmp/docker/images) in which Docker image archives
      (result of 'docker save') are stored.
      (default: https://registry-1.docker.io)
    </td>
  </tr>
  <tr>
    <td>
      --docker_store_dir=VALUE
    </td>
    <td>
      Directory the Docker provisioner will store images in.
      (default: /tmp/mesos/store/docker)
    </td>
  </tr>
  <tr>
    <td>
      --docker_remove_delay=VALUE
    </td>
    <td>
      The amount of time to wait before removing Docker containers
      (e.g., <code>3days</code>, <code>2weeks</code>, etc).
      (default: 6hrs)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]docker_kill_orphans
    </td>
    <td>
      Enable docker containerizer to kill orphaned containers.
      You should consider setting this to false when you launch multiple
      slaves in the same OS, to avoid one of the DockerContainerizer removing
      docker tasks launched by other slaves.
      (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --docker_socket=VALUE
    </td>
    <td>
      The UNIX socket path to be mounted into the docker executor container to
      provide docker CLI access to the docker daemon. This must be the path used
      by the slave's docker image.
      (default: /var/run/docker.sock)
    </td>
  </tr>
  <tr>
    <td>
      --docker_mesos_image=VALUE
    </td>
    <td>
      The docker image used to launch this mesos slave instance.
      If an image is specified, the docker containerizer assumes the slave
      is running in a docker container, and launches executors with
      docker containers in order to recover them when the slave restarts and
      recovers.
    </td>
  </tr>
  <tr>
    <td>
      --docker_stop_timeout=VALUE
    </td>
    <td>
      The time as a duration for docker to wait after stopping an instance
      before it kills that instance. (default: 0secs)
    </td>
  </tr>
  <tr>
    <td>
      --sandbox_directory=VALUE
    </td>
    <td>
      The absolute path for the directory in the container where the
      sandbox is mapped to.
      (default: /mnt/mesos/sandbox)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]enforce_container_disk_quota
    </td>
    <td>
      Whether to enable disk quota enforcement for containers. This flag
      is used for the 'posix/disk' isolator. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --executor_environment_variables
    </td>
    <td>
      JSON object representing the environment variables that should be
      passed to the executor, and thus subsequently task(s).
      By default the executor will inherit the slave's environment variables.
      Example:
<pre><code>{
  "PATH": "/bin:/usr/bin",
  "LD_LIBRARY_PATH": "/usr/local/lib"
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --executor_registration_timeout=VALUE
    </td>
    <td>
      Amount of time to wait for an executor
      to register with the slave before considering it hung and
      shutting it down (e.g., <code>60secs</code>, <code>3mins</code>, etc)
      (default: 1mins)
    </td>
  </tr>
  <tr>
    <td>
      --executor_shutdown_grace_period=VALUE
    </td>
    <td>
      Amount of time to wait for an executor to shut down.
      (e.g., <code>60secs</code>, <code>3mins</code>, etc). (default: 5secs)
    </td>
  </tr>
  <tr>
    <td>
      --frameworks_home=VALUE
    </td>
    <td>
      Directory path prepended to relative executor URIs. (empty by default)
    </td>
  </tr>
  <tr>
    <td>
      --gc_delay=VALUE
    </td>
    <td>
      Maximum amount of time to wait before cleaning up
      executor directories (e.g., 3days, 2weeks, etc).
      <p/>
      Note that this delay may be shorter depending on
      the available disk usage. (default: 1weeks)
    </td>
  </tr>
  <tr>
    <td>
      <a name="gc_disk_headroom"></a>
      --gc_disk_headroom=VALUE
    </td>
    <td>
      Adjust disk headroom used to calculate maximum executor
      directory age. Age is calculated by:</p>
      <code>gc_delay * max(0.0, (1.0 - gc_disk_headroom - disk usage))</code>
      every <code>--disk_watch_interval</code> duration.
      <code>gc_disk_headroom</code> must be a value between 0.0 and 1.0
      (default: 0.1)
    </td>
  </tr>
  <tr>
    <td>
      --hadoop_home=VALUE
    </td>
    <td>
      Path to find Hadoop installed (for fetching framework executors from HDFS)
      (no default, look for <code>HADOOP_HOME</code> in environment or find
      hadoop on <code>PATH</code>).
    </td>
  </tr>
  <tr>
    <td>
      --hooks=VALUE
    </td>
    <td>
      A comma-separated list of hook modules to be
      installed inside master.
    </td>
  </tr>
  <tr>
    <td>
      --hostname=VALUE
    </td>
    <td>
      The hostname the agent node should report.<br>
      If left unset, the hostname is resolved from the IP address
      that the slave binds to; unless the user explicitly prevents
      that, using --no-hostname_lookup, in which case the IP itself
      is used.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]hostname_lookup
    </td>
    <td>
      Whether we should execute a lookup to find out the server's hostname,
      if not explicitly set (via, e.g., `--hostname`).
      True by default; if set to 'false' it will cause Mesos
      to use the IP address, unless the hostname is explicitly set.
    </td>
  </tr>
  <tr>
    <td>
      --isolation=VALUE
    </td>
    <td>
      Isolation mechanisms to use, e.g., 'posix/cpu,posix/mem', or
      'cgroups/cpu,cgroups/mem', or network/port_mapping
      (configure with flag: --with-network-isolator to enable),
      or 'external', or load an alternate isolator module using
      the <code>--modules</code> flag. Note that this flag is only
      relevant for the Mesos Containerizer.
      (default: posix/cpu,posix/mem)
    </td>
  </tr>
  <tr>
    <td>
      --launcher=VALUE
    </td>
    <td>
      The launcher to be used for Mesos containerizer. It could either be
      'linux' or 'posix'. The Linux launcher is required for cgroups
      isolation and for any isolators that require Linux namespaces such as
      network, pid, etc. If unspecified, the slave will choose the Linux
      launcher if it's running as root on Linux.
    </td>
  </tr>
  <tr>
    <td>
      --launcher_dir=VALUE
    </td>
    <td>
      Directory path of Mesos binaries. Mesos would find health-check, fetcher,
      containerizer and executor binary files under this directory.
      (default: /usr/local/libexec/mesos)
    </td>
  </tr>
  <tr>
    <td>
      --image_providers=VALUE
    </td>
    <td>
      Comma-separated list of supported image providers, e.g., 'APPC,DOCKER'.
    </td>
  </tr>
  <tr>
    <td>
      --modules=VALUE
    </td>
    <td>
      List of modules to be loaded and be available to the internal
      subsystems.
      <p/>
      Remember you can also use the <code>file:///path/to/file</code> or
      <code>/path/to/file</code> argument value format to have the value read
      from a file.<p/>
      Use <code>--modules="{...}"</code> to specify the list of modules inline.
      <p/>
      JSON file example:
<pre><code>
{
  "libraries": [
    {
      "file": "/path/to/libfoo.so",
      "modules": [
        {
          "name": "org_apache_mesos_bar",
          "parameters": [
            {
              "key": "X",
              "value": "Y"
            }
          ]
        },
        {
          "name": "org_apache_mesos_baz"
        }
      ]
    },
    {
      "name": "qux",
      "modules": [
        {
          "name": "org_apache_mesos_norf"
        }
      ]
    }
  ]
}</code></pre>
    </td>
  </tr>
  <tr>
    <td>
      --oversubscribed_resources_interval=VALUE
    </td>
    <td>
      The slave periodically updates the master with the current estimation
      about the total amount of oversubscribed resources that are allocated
      and available. The interval between updates is controlled by this flag.
      (default: 15secs)
    </td>
  </tr>
  <tr>
    <td>
      --perf_duration=VALUE
    </td>
    <td>
      Duration of a perf stat sample. The duration must be less
      that the <code>perf_interval</code>. (default: 10secs)
    </td>
  </tr>
  <tr>
    <td>
      --perf_events=VALUE
    </td>
    <td>
      List of command-separated perf events to sample for each container
      when using the perf_event isolator. (none by default)
      <p/>
      Run command 'perf list' to see all events. Event names are
      sanitized by downcasing and replacing hyphens with underscores
      when reported in the PerfStatistics protobuf, e.g., cpu-cycles
      becomes cpu_cycles; see the PerfStatistics protobuf for all names.
    </td>
  </tr>
  <tr>
    <td>
      --perf_interval=VALUE
    </td>
    <td>
      Interval between the start of perf stat samples. Perf samples are
      obtained periodically according to <code>perf_interval</code> and the most
      recently obtained sample is returned rather than sampling on
      demand. For this reason, <code>perf_interval</code> is independent of the
      resource monitoring interval. (default: 1mins)
    </td>
  </tr>
  <tr>
    <td>
      --qos_controller=VALUE
    </td>
    <td>
      The name of the QoS Controller to use for oversubscription.
    </td>
  </tr>
  <tr>
    <td>
      --qos_correction_interval_min=VALUE
    </td>
    <td>
      The slave polls and carries out QoS corrections from the QoS
      Controller based on its observed performance of running tasks.
      The smallest interval between these corrections is controlled by
      this flag. (default: 0secs)
    </td>
  </tr>
  <tr>
    <td>
      --recover=VALUE
    </td>
    <td>
      Whether to recover status updates and reconnect with old executors.
      <p/>
      Valid values for 'recover' are
      <p/>
      reconnect: Reconnect with any old live executors.
      <p/>
      cleanup  : Kill any old live executors and exit.
      <p/>
      Use this option when doing an incompatible slave or executor upgrade.
      (default: reconnect)
    </td>
  </tr>
  <tr>
    <td>
      --recovery_timeout=VALUE
    </td>
    <td>
      Amount of time allotted for the slave to recover. If the slave takes
      longer than recovery_timeout to recover, any executors that are
      waiting to reconnect to the slave will self-terminate.
      (default: 15mins)
    </td>
  </tr>
  <tr>
    <td>
      --registration_backoff_factor=VALUE
    </td>
    <td>
      Slave initially picks a random amount of time between [0, b], where
      b = registration_backoff_factor, to (re-)register with a new master.
      <p/>
      Subsequent retries are exponentially backed off based on this
      interval (e.g., 1st retry uses a random value between [0, b * 2^1],
      2nd retry between [0, b * 2^2], 3rd retry between [0, b * 2^3] etc)
      up to a maximum of <code>1mins</code>. (default: 1secs)
    </td>
  </tr>
  <tr>
    <td>
      --resource_estimator=VALUE
    </td>
    <td>
      The name of the resource estimator to use for oversubscription.
    </td>
  </tr>
  <tr>
    <td>
      --resources=VALUE
    </td>
    <td>
      <p>
      Total consumable resources per slave. Can be provided in JSON format or as
      a semicolon-delimited list of key:value pairs, with the role optionally
      specified.
      </p><p>
      As a key:value list:
      </p><p>
      <code>name(role):value;name:value...</code>
      </p><p>
      To use JSON, pass a JSON-formatted string or use --resources=filepath to
      specify the resources via a file containing a JSON-formatted string.
      'filepath' can be of the form 'file:///path/to/file' or '/path/to/file'.
      </p><p>
      Example JSON:
</p><pre><code>[
  {
    "name": "cpus",
    "type": "SCALAR",
    "scalar": {
      "value": 24
    }
  },
  {
    "name": "mem",
    "type": "SCALAR",
    "scalar": {
      "value": 24576
    }
  }
]</code></pre>
      <p>
      See the documentation on
      <a href="/documentation/latest/attributes-resources/">Attributes and
      Resources</a> for more information.
      </p>
    </td>
  </tr>
  <tr>
    <td>
      --[no-]revocable_cpu_low_priority
    </td>
    <td>
      Run containers with revocable CPU at a lower priority than
      normal containers (non-revocable cpu). Currently only
      supported by the cgroups/cpu isolator. (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --slave_subsystems=VALUE
    </td>
    <td>
      List of comma-separated cgroup subsystems to run the slave binary
      in, e.g., <code>memory,cpuacct</code>. The default is none.
      Present functionality is intended for resource monitoring and
      no cgroup limits are set, they are inherited from the root mesos
      cgroup.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]strict
    </td>
    <td>
      If <code>strict=true</code>, any and all recovery errors are considered
      fatal.
      <p/>
      If <code>strict=false</code>, any expected errors (e.g., slave cannot
      recover information about an executor, because the slave died right before
      the executor registered.) during recovery are ignored and as much
      state as possible is recovered. (default: true)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]switch_user
    </td>
    <td>
      If set to <code>true</code>, the agent will attempt to run tasks as
      the <code>user</code> who launched them (as defined in FrameworkInfo).
      Note that this requires <code>setuid</code> permission and that the given
      <code>user</code> exists on the agent).
      If the user does not exist, an error occurs and the task will fail.
      If set to <code>false</code>, tasks will be run as the same user as the
      Mesos agent process. (default: true)
      <b>NOTE</b> This feature is not yet supported on Windows agents, and
      therefore the flag currently does not exist on that platform.
    </td>
  </tr>
  <tr>
    <td>
      --fetcher_cache_size=VALUE
    </td>
    <td>
      Size of the fetcher cache in Bytes.
      (default: 2 GB)
    </td>
  </tr>
  <tr>
    <td>
      --fetcher_cache_dir=VALUE
    </td>
    <td>
      Parent directory for fetcher cache directories (one subdirectory
      per slave). By default this directory is held inside the work
      directory, so everything can be deleted or archived in one
      swoop, in particular during testing. However, a typical
      production scenario is to use a separate cache volume. First, it
      is not meant to be backed up. Second, you want to avoid that
      sandbox directories and the cache directory can interfere with
      each other in unpredictable ways by occupying shared space. So
      it is recommended to set the cache directory explicitly.
      (default: /tmp/mesos/fetch)
    </td>
  </tr>
  <tr>
    <td>
      --work_dir=VALUE
    </td>
    <td>
      Directory path to place framework work directories.
      (default: /tmp/mesos)
    </td>
  </tr>
</table>

*Flags available when configured with `--with-network-isolator`*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --ephemeral_ports_per_container=VALUE
    </td>
    <td>
      Number of ephemeral ports allocated to a container by the network
      isolator. This number has to be a power of 2.
      (default: 1024)
    </td>
  </tr>
  <tr>
    <td>
      --eth0_name=VALUE
    </td>
    <td>
      The name of the public network interface (e.g., eth0). If it is
      not specified, the network isolator will try to guess it based
      on the host default gateway.
    </td>
  </tr>
  <tr>
    <td>
      --lo_name=VALUE
    </td>
    <td>
      The name of the loopback network interface (e.g., lo). If it is
      not specified, the network isolator will try to guess it.
    </td>
  </tr>
  <tr>
    <td>
      --egress_rate_limit_per_container=VALUE
    </td>
    <td>
      The limit of the egress traffic for each container, in Bytes/s.
      If not specified or specified as zero, the network isolator will
      impose no limits to containers' egress traffic throughput.
      This flag uses the Bytes type, defined in stout.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]-egress_unique_flow_per_container
    </td>
    <td>
      Whether to assign an individual flow for each container for the
      egress traffic. fq_codel qdisc is used to isolate egress traffic
      for containers. This flag is used for the 'network/port_mapping'
      isolator. Note, fq_codel qdisc is installed at root and is not
      removed after mesos slave exits. (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --egress_flow_classifier_parent=root/X:Y
    </td>
    <td>
      When --egress_unique_flow_per_container is enabled, we need to install
      a flow classifier (fq_codel qdisc) on egress side. This flag specifies
      where to install it in the whole qdisc hierarchy. By default, we install
      it at root. But, for example, if you have already installed an HTB qdisc
      at root, you may want this to be installed in other place than root,
      specify an HTB class ID (X:Y) as its parent. X:Y must be hexadecimal
      numbers without "0x" prefix. Note, it is always your responsibility to
      ensure the whole qdisc hierarchy is meaningful and correct.
    </td>
  </tr>
  <tr>
    <td>
      --[no-]network_enable_socket_statistics_summary
    </td>
    <td>
      Whether to collect socket statistics summary for each container.
      This flag is used for the 'network/port_mapping' isolator.
      (default: false)
    </td>
  </tr>
  <tr>
    <td>
      --[no-]network_enable_socket_statistics_details
    </td>
    <td>
      Whether to collect socket statistics details (e.g., TCP RTT) for
      each container. This flag is used for the 'network/port_mapping'
      isolator. (default: false)
    </td>
  </tr>
</table>


## Libprocess Options

*The bundled libprocess library can be controlled with the following environment variables.*

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Variable
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      LIBPROCESS_IP
    </td>
    <td>
      Sets the IP address for communication to and from libprocess.
    </td>
  </tr>
  <tr>
    <td>
      LIBPROCESS_PORT
    </td>
    <td>
      Sets the port for communication to and from libprocess.
    </td>
  </tr>
  <tr>
    <td>
      LIBPROCESS_ADVERTISE_IP
    </td>
    <td>
      If set, this provides the IP address that will be advertised to
      the outside world for communication to and from libprocess.
      This is useful, for example, for containerized tasks in which
      communication is bound locally to a non-public IP that will be
      inaccessible to the master.
    </td>
  </tr>
  <tr>
    <td>
      LIBPROCESS_ADVERTISE_PORT
    </td>
    <td>
      If set, this provides the port that will be advertised to the
      outside world for communication to and from libprocess. Note that
      this port will not actually be bound (the local LIBPROCESS_PORT
      will be), so redirection to the local IP and port must be
      provided separately.
    </td>
  </tr>
</table>


## Mesos Build Configuration Options

###The configure script has the following flags for optional features:

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --enable-shared[=PKGS]
    </td>
    <td>
      Build shared libraries. [default=yes]
    </td>
  </tr>
  <tr>
    <td>
      --enable-static[=PKGS]
    </td>
    <td>
      Build static libraries. [default=yes]
    </td>
  </tr>
  <tr>
    <td>
      --enable-fast-install[=PKGS]
    </td>
    <td>
      Optimize for fast installation. [default=yes]
    </td>
  </tr>
  <tr>
    <td>
      --enable-libevent
    </td>
    <td>
      Use <a href="https://github.com/libevent/libevent">libevent</a>
      instead of libev for the libprocess event loop. Note that the libevent
      version 2+ development package is required. [default=no]
    </td>
  </tr>
  <tr>
    <td>
      --enable-ssl
    </td>
    <td>
      Enable <a href="/documentation/latest/ssl">SSL</a> for libprocess
      communication. Note that <code>--enable-libevent</code> is currently
      required for SSL functionality. [default=no]
    </td>
  </tr>
  <tr>
    <td>
      --disable-libtool-lock
    </td>
    <td>
      Avoid locking. Note that this might break parallel builds.
    </td>
  </tr>
  <tr>
    <td>
      --disable-java
    </td>
    <td>
      Don't build Java bindings.
    </td>
  </tr>
  <tr>
    <td>
      --disable-python
    </td>
    <td>
      Don't build Python bindings.
    </td>
  </tr>
  <tr>
    <td>
      --enable-debug
    </td>
    <td>
      Whether debugging is enabled. If CFLAGS/CXXFLAGS are set, this
      option won't change them. [default=no]
    </td>
  </tr>
  <tr>
    <td>
      --enable-optimize
    </td>
    <td>
      Whether optimizations are enabled. If CFLAGS/CXXFLAGS are set,
      this option won't change them. [default=no]
    </td>
  </tr>
  <tr>
    <td>
      --disable-bundled
    </td>
    <td>
      Configures Mesos to build against preinstalled dependencies
      instead of bundled libraries.
    </td>
  </tr>
  <tr>
    <td>
      --disable-bundled-distribute
    </td>
    <td>
      Excludes building and using the bundled distribute package in lieu of an
      installed version in <code>PYTHONPATH</code>.
    </td>
  </tr>
  <tr>
    <td>
      --disable-bundled-pip
    </td>
    <td>
      Excludes building and using the bundled pip package in lieu of an
      installed version in <code>PYTHONPATH</code>.
    </td>
  </tr>
  <tr>
    <td>
      --disable-bundled-wheel
    </td>
    <td>
      Excludes building and using the bundled wheel package in lieu of an
      installed version in <code>PYTHONPATH</code>.
    </td>
  </tr>
  <tr>
    <td>
      --disable-python-dependency-install
    </td>
    <td>
      When the python packages are installed during make install, no external
      dependencies will be downloaded or installed.
    </td>
  </tr>
</table>

### The configure script has the following flags for optional packages:

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Flag
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      --with-gnu-ld
    </td>
    <td>
      Assume the C compiler uses GNU <code>ld</code>. [default=no]
    </td>
  </tr>
  <tr>
    <td>
      --with-sysroot=DIR
    </td>
    <td>
      Search for dependent libraries within <code>DIR</code>
      (or the compiler's sysroot if not specified).
    </td>
  </tr>
  <tr>
    <td>
      --with-zookeeper[=DIR]
    </td>
    <td>
      Excludes building and using the bundled ZooKeeper package in lieu of an
      installed version at a location prefixed by the given path.
    </td>
  </tr>
  <tr>
    <td>
      --with-leveldb[=DIR]
    </td>
    <td>
      Excludes building and using the bundled LevelDB package in lieu of an
      installed version at a location prefixed by the given path.
    </td>
  </tr>
  <tr>
    <td>
      --with-glog[=DIR]
    </td>
    <td>
      excludes building and using the bundled glog package in lieu of an
      installed version at a location prefixed by the given path.
    </td>
  </tr>
  <tr>
    <td>
      --with-protobuf[=DIR]
    </td>
    <td>
      Excludes building and using the bundled protobuf package in lieu of an
      installed version at a location prefixed by the given path.
    </td>
  </tr>
  <tr>
    <td>
      --with-gmock[=DIR]
    </td>
    <td>
      Excludes building and using the bundled gmock package in lieu of an
      installed version at a location prefixed by the given path.
    </td>
  </tr>
  <tr>
    <td>
      --with-curl[=DIR]
    </td>
    <td>
      Specify where to locate the curl library.
    </td>
  </tr>
  <tr>
    <td>
      --with-sasl[=DIR]
    </td>
    <td>
      Specify where to locate the sasl2 library.
    </td>
  </tr>
  <tr>
    <td>
      --with-zlib[=DIR]
    </td>
    <td>
      Specify where to locate the zlib library.
    </td>
  </tr>
  <tr>
    <td>
      --with-apr[=DIR]
    </td>
    <td>
      Specify where to locate the apr-1 library.
    </td>
  </tr>
  <tr>
    <td>
      --with-svn[=DIR]
    </td>
    <td>
      Specify where to locate the svn-1 library.
    </td>
  </tr>
  <tr>
    <td>
      --with-libevent[=DIR]
    </td>
    <td>
      Specify where to locate the libevent library.
    </td>
  </tr>
  <tr>
    <td>
      --with-ssl[=DIR]
    </td>
    <td>
      Specify where to locate the ssl library.
    </td>
  </tr>
  <tr>
    <td>
      --with-network-isolator
    </td>
    <td>
      Builds the network isolator.
    </td>
  </tr>
  <tr>
    <td>
      --with-nl[=DIR]
    </td>
    <td>
      Specify where to locate the
      <a href="https://www.infradead.org/~tgr/libnl/">libnl3</a> library,
      which is required for the network isolator.
    </td>
  </tr>
</table>

### Some influential environment variables for configure script:

Use these variables to override the choices made by `configure` or to help
it to find libraries and programs with nonstandard names/locations.

<table class="table table-striped">
  <thead>
    <tr>
      <th width="30%">
        Variable
      </th>
      <th>
        Explanation
      </th>
    </tr>
  </thead>
  <tr>
    <td>
      JAVA_HOME
    </td>
    <td>
      Location of Java Development Kit (JDK).
    </td>
  </tr>
  <tr>
    <td>
      JAVA_CPPFLAGS
    </td>
    <td>
      Preprocessor flags for JNI.
    </td>
  </tr>
  <tr>
    <td>
      JAVA_JVM_LIBRARY
    </td>
    <td>
      Full path to <code>libjvm.so</code>.
    </td>
  </tr>
  <tr>
    <td>
      MAVEN_HOME
    </td>
    <td>
      Looks for <code>mvn</code> at <code>MAVEN_HOME/bin/mvn</code>.
    </td>
  </tr>
  <tr>
    <td>
      PROTOBUF_JAR
    </td>
    <td>
      Full path to protobuf jar on prefixed builds.
    </td>
  </tr>
  <tr>
    <td>
      PYTHON
    </td>
    <td>
      Which Python interpreter to use.
    </td>
  </tr>
  <tr>
    <td>
      PYTHON_VERSION
    </td>
    <td>
      The installed Python version to use, for example '2.3'. This string will
      be appended to the Python interpreter canonical name.
    </td>
  </tr>
</table>
