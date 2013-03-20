/*
 * pg commands PgMonitor.cc
 */

COMMAND("pg stat", "pg stat help")
COMMAND("pg getmap", "pg getmap help")
COMMAND("pg send_pg_creates", "send_pg_creates help")
COMMAND("pg dump type=CephChoices,strings=all|summary|sum|pools|osds|pgs,n=N,name=dumpcontents", "dump help")
COMMAND("pg dump_json type=CephChoices,strings=all|summary|sum|pools|osds|pgs,n=N,name=dumpcontents", "dump_json help")
COMMAND("pg dump_pools_json", "dump_pools_json help")
COMMAND("pg dump_stuck type=CephChoices,strings=inactive|unclean|stale,n=N,name=stuckops", "dump_stuck help")
COMMAND("pg map type=CephPgid,name=pgid", "pg map <pgid> help")
COMMAND("pg scrub type=CephPgid,name=pgid", "pg scrub help")
COMMAND("pg deep-scrub type=CephPgid,name=pgid", "pg deep-scrub help")
COMMAND("pg repair type=CephPgid,name=pgid", "pg repair help")
COMMAND("pg debug type=CephChoices,strings=unfound_objects_exist|degraded_pgs_exist,name=debugop", "pg debug help")
COMMAND("pg force_create_pg type=CephPgid,name=pgid", "pg force_create_pg help")
COMMAND("pg set_full_ratio type=CephFloat,range=0.0|1.0,name=ratio", "pg set_full_ratio help")
COMMAND("pg set_nearfull_ratio type=CephFloat,range=0.0|1.0,name=ratio", "pg set_nearfull_ratio help")

/*
 * auth commands AuthMonitor.cc
 */

COMMAND("auth export type=CephName,name=entity,req=false", "write keyring for requested entity, or master keyring if none given")
COMMAND("auth get type=CephName,name=entity", "write keyring file with requested key")
COMMAND("auth get-key type=CephName,name=entity", "display requested key")
COMMAND("auth print-key type=CephName,name=entity", "display requested key")
COMMAND("auth print_key type=CephName,name=entity", "display requested key")
COMMAND("auth list", "list authentication state")
COMMAND("auth import", "auth import: read keyring file from input")
COMMAND("auth add type=CephName,name=entity type=CephString,name=caps,n=N,req=false", "add auth info for <name> from input file, or random key if no input given, and/or any caps specified in the command")
COMMAND("auth get-or-create-key type=CephName,name=entity type=CephString,name=caps,n=N,req=false", "get, or add, key for <name> from system/caps pairs specified in the command.  If key already exists, any given caps must match the existing caps for that key.")
COMMAND("auth get-or-create type=CephName,name=entity type=CephString,name=caps,n=N,req=false", "add auth info for <name> from input file, or random key if no input given, and/or any caps specified in the command")
COMMAND("auth caps type=CephName,name=entity type=CephString,name=caps,n=N", "update caps for <name> from caps specified in the command")
COMMAND("auth caps type=CephName,name=entity type=CephString,name=caps,n=N", "update caps for <name> from caps specified in the command")
COMMAND("auth del type=CephName,name=entity", "delete all caps for <name>")

/*
 * Monitor commands (Monitor.cc)
 */
COMMAND("fsid", "show cluster FSID/UUID")
COMMAND("log type=CephString,n=N,name=logtext", "log supplied text to the monitor log")
COMMAND("stop_cluster", "DEPRECATED")
COMMAND("injectargs type=CephString,n=N,name=injected_args", "inject config arguments into monitor")
COMMAND("status", "show cluster status")
COMMAND("health type=CephChoices,strings=detail,name=detail,req=false", "show cluster health")
COMMAND("df type=CephChoices,strings=detail,name=detail,req=false", "show cluster free space stats")
COMMAND("report", "report full status of cluster")
COMMAND("quorum_status", "report status of monitor quorum")
COMMAND("mon_status", "report status of monitors")
COMMAND("sync status", "report status of monitors")
COMMAND("sync force type=CephChoices,strings=--yes-i-really-mean-it,name=validate1 type=CephChoices,strings=--i-know-what-i-am-doing,name=validate2", "force sync of and clear monitor store")
COMMAND("heap type=CephChoices,strings=dump|start_profiler|stop_profiler|release|stats,name=heapcmd", "show heap usage info (available only if compiled with tcmalloc")
COMMAND("quorum type=CephChoices,strings=enter|exit,n=1,name=quorumcmd", "enter or exit quorum")

/*
 * MDS commands (MDSMonitor.cc)
 */
#include "include/ceph_fs.h"

COMMAND("mds stat", "show MDS status")
COMMAND("mds dump type=CephInt,req=false,range=0,name=epoch", "dump info, optionally from epoch")
COMMAND("mds getmap type=CephInt,req=false,range=0,name=epoch", "get MDS map, optionally from epoch")
COMMAND("mds tell type=CephString,name=who type=CephString,name=args,n=N", "send command to particular mds")
COMMAND("mds compat type=CephChoices,strings=show|help", "mds compat")
COMMAND("mds stop type=CephString,name=who", "stop mds")
COMMAND("mds deactivate type=CephString,name=who", "stop mds")
COMMAND("mds set_max_mds type=CephInt,name=maxmds,range=0", "set max MDS index")
COMMAND("mds setmap type=CephInt,name=epoch,range=0", "set mds map for <epoch> to input file")
// arbitrary limit 0-20 below; worth standing on head to make it
// relate to actual state definitions?
COMMAND("mds set_state type=CephInt,name=gid,range=0 type=CephInt,name=state,range=0|20", "set mds state of <gid> to <numeric-state>")
COMMAND("mds fail type=CephName,name=who", "force mds to status failed")
COMMAND("mds rm type=CephInt,name=gid,range=0 type=CephName,name=who", "remove nonactive mds")
COMMAND("mds rmfailed type=CephInt,range=0,name=who", "remove failed mds")
COMMAND("mds cluster_down", "take MDS cluster down")
COMMAND("mds cluster_up", "take MDS cluster down")
COMMAND("mds compat rm_compat type=CephInt,name=feature,range=0 ", "remove compatible feature")
COMMAND("mds compat rm_incompat type=CephInt,name=feature,range=0", "remove incompatible feature")
COMMAND("mds add_data_pool type=CephInt,name=poolid,range=0", "add data pool <poolid>")
COMMAND("mds remove_data_pool type=CephInt,name=poolid,range=0", "remove data pool <poolid>")
COMMAND("mds newfs type=CephInt,name=metadata,range=0 type=CephInt,name=data,range=0 type=CephChoices,strings=--yes-i-really-mean-it,name=sure", "make new filesystom using pools <metadata> and <data>")


/*
 * Monmap commands
 */
COMMAND("mon stat", "dump monitor status (monmap)")
COMMAND("mon getmap type=CephInt,range=0,name=epoch,req=false", "get monmap")
COMMAND("mon tell type=CephString,name=who type=CephString,n=N,name=args", "send command to specific monitor(s)")
COMMAND("mon add type=CephString,name=name type=CephIPAddr,name=addr", "add new monitor named <name> at <addr>")
COMMAND("mon remove type=CephString,name=name", "remove monitor named <name>")

/*
 * OSD commands
 */
COMMAND("osd stat", "print summary of OSD map")
COMMAND("osd dump", "print summary of OSD map")
COMMAND("osd tree type=CephInt,range=0,name=epoch,req=false", "print OSD tree")
COMMAND("osd ls type=CephInt,range=0,name=epoch", "show all OSD ids")
COMMAND("osd getmap type=CephInt,range=0,name=epoch,req=false", "get OSD map")
COMMAND("osd getcrushmap type=CephInt,range=0,name=epoch", "get CRUSH map")
COMMAND("osd getmaxosd", "show largest OSD id")
COMMAND("osd tell type=CephString,name=who type=CephString,name=args,n=N", "send command to particular osd")
COMMAND("osd find type=CephInt,name=id,range=0", "find osd <id> in the CRUSH map and show its location")
COMMAND("osd map type=CephPoolname,name=pool type=CephObjectname,name=object", "find pg for <object> in <pool>")
COMMAND("osd scrub type=CephString,name=who", "initiate scrub on osd <who>")
COMMAND("osd deep-scrub type=CephString,name=who", "initiate deep-scrub on osd <who>")
COMMAND("osd repair type=CephString,name=who", "initiate repair on osd <who>")
COMMAND("osd lspools type=CephInt,name=auid", "list pools")
COMMAND("osd blacklist ls", "show blacklisted clients")
COMMAND("osd crush rule list", "list crush rules")
COMMAND("osd crush rule ls", "list crush rules")
COMMAND("osd crush rule dump", "dump crush rules")
COMMAND("osd crush dump", "dump crush map")
COMMAND("osd setcrushmap", "set crush map from input file")
COMMAND("osd crush set", "set crush map from input file")
COMMAND("osd crush set type=CephInt,name=id,range=0 type=CephString,name=name type=CephFloat,name=weight,range=0.0 type=CephString,name=args,n=N", "set crushmap entry for <id> to <weight> with location <args>")
COMMAND("osd crush create-or-move type=CephInt,name=id,range=0 type=CephFloat,name=weight,range=0.0 type=CephString,name=args,n=N", "create entry or move existing entry for <id> <weight> at/to location <args>")
COMMAND("osd crush move type=CephString,name=name type=CephString,name=args,n=N", "move existing entry for <name> to location <args>")
COMMAND("osd crush rm type=CephString,name=name", "remove <name> from crush map")
COMMAND("osd crush remove type=CephString,name=name", "remove <name> from crush map")
COMMAND("osd crush reweight type=CephString,name=name type=CephFloat,name=weight,range=0.0", "change <name>'s weight to <weight> in crush map")
COMMAND("osd crush tunables type=CephChoices,strings=legacy|argonaut|bobtail|optimal|default,name=profile", "set crush tunables values to <profile>")
COMMAND("osd crush rule create-simple type=CephString,name=name type=CephString,name=root type=CephString,name=type", "create crush rule <name> in <root> of type <type>")
COMMAND("osd crush rule rm type=CephString,name=name", "remove crush rule <name>")
COMMAND("osd setmaxosd type=CephInt,name=newmax,range=0", "set new maximum osd value")
COMMAND("osd pause", "pause osd")
COMMAND("osd unpause", "unpause osd")
COMMAND("osd set type=CephChoices,name=key,strings=pause|noup|nodown|noout|noin|nobackfile|norecover", "set <key>")
COMMAND("osd unset type=CephChoices,name=key,strings=pause|noup|nodown|noout|noin|nobackfile|norecover", "unset <key>")
COMMAND("osd cluster_snap", "take cluster snapshot (disabled)")
// can't do array in value, at least not yet
COMMAND("osd down type=CephString,name=ids,n=N", "set osd(s) <id> [<id>...] down")
COMMAND("osd out type=CephString,name=ids,n=N", "set osd(s) <id> [<id>...] out")
COMMAND("osd in type=CephString,name=ids,n=N", "set osd(s) <id> [<id>...] in")
COMMAND("osd rm type=CephString,name=ids,n=N", "set osd(s) <id> [<id>...] in")
COMMAND("osd reweight type=CephInt,name=id,range=0 type=CephFloat,name=weight,range=0.0|1.0", "reweight osd to 0.0 < <weight> < 1.0")
COMMAND("osd lost type=CephInt,name=id,range=0 type=CephChoices,strings=--yes-i-really-mean-it,name=sure", "mark osd as permanently lost, which MAY LOSE DATA")
COMMAND("osd create type=CephUUID,name=uuid,req=false", "create new osd (with optional UUID)")
COMMAND("osd blacklist type=CephChoices,name=blacklistop,strings=add|rm type=CephEntityAddr,name=addr type=CephFloat,name=expire,range=0.0,req=false", "add (optionally until <expire> seconds from now) or remove <addr> from blacklist")
COMMAND("osd pool mksnap type=CephPoolname,name=pool type=CephString,name=snap", "make snapshot <snap> in <pool>")
COMMAND("osd pool mksnap type=CephPoolname,name=pool type=CephString,name=snap", "remove snapshot <snap> from <pool>")
COMMAND("osd pool create type=CephPoolname,name=pool type=CephInt,name=pg_num,range=0 type=CephInt,name=pgp_num,range=0,req=false", "create pool")
COMMAND("osd pool delete type=CephPoolname,name=pool type=CephPoolname,name=pool2 type=CephChoices,name=sure,strings=--yes-i-really-really-mean-it", "delete pool (say pool twice, add --yes-i-really-really-mean-it")
COMMAND("osd pool rename type=CephPoolname,name=srcpool type=CephPoolname,name=destpool", "rename <srcpool> to <destpool>")
COMMAND("osd pool get type=CephPoolname,name=pool type=CephChoices,name=var,strings=size|min_size|crash_replay_interval|pg_num|pgp_num|crush_ruleset type=CephInt,name=val,range=0", "set pool parameter <var> to <val>")
COMMAND("osd pool set type=CephPoolname,name=pool type=CephChoices,name=var,strings=size|min_size|crash_replay_interval|pg_num|pgp_num|crush_ruleset type=CephChoices,name=sure,strings=--allow-experimental-feature,req=false", "get pool parameter <var>")
COMMAND("osd reweight-by-utilization type=CephInt,name=oload,range=0", "reweight OSDs by utilization <oload XXX>")
COMMAND("osd thrash type=CephInt,name=num_epochs,range=0", "thrash OSDs for <num_epochs>")











