// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2013 Inktank Storage, Inc.
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License version 2, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#include "common/cmdparse.h"
#include "json_spirit/json_spirit.h"

// Parse JSON in vector cmd into a map from field to map of values
// (use mValue/mObject)
// 'cmd' should not disappear over lifetime of map
// 'mapp' points to the caller's map
// 'ss' captures any errors during JSON parsing; if function returns
// false, ss is valid

using namespace std;

bool
cmdmap_from_json(vector<string> cmd, map<string, cmd_vartype> *mapp, stringstream &ss)
{
  json_spirit::mValue v;

  string fullcmd;
  // First, join all cmd strings
  for (vector<string>::iterator it = cmd.begin();
       it != cmd.end(); it++)
    fullcmd += *it;

  try {
    if (!json_spirit::read(fullcmd, v))
      throw runtime_error("unparseable JSON" + fullcmd);
    if (v.type() != json_spirit::obj_type)
      throw(runtime_error("not JSON object" + fullcmd));

    // allocate new mObject (map) to return
    // make sure all contents are simple types (not arrays or objects)
    json_spirit::mObject o = v.get_obj();
    for (map<string, json_spirit::mValue>::iterator it = o.begin();
	 it != o.end(); it++) {

      // ok, marshal it into our string->cmd_vartype map, or throw an
      // exception if it's not a simple datatype.  This is kind of
      // annoying, since json_spirit has a boost::variant inside it
      // already, but it's not public.  Oh well.

      switch (it->second.type()) {

      case json_spirit::obj_type:
      default:
	throw(runtime_error("JSON array/object not allowed" + fullcmd));
        break;

      case json_spirit::array_type:
	{
	  // array is a vector of values.  Unpack it to a vector
	  // of strings, the only type we handle.
	  vector<json_spirit::mValue> spvals = it->second.get_array();
	  vector<string> *outvp = new vector<string>;
	  for (vector<json_spirit::mValue>::iterator sv = spvals.begin();
	       sv != spvals.end(); sv++) {
	    if (sv->type() != json_spirit::str_type)
	      throw(runtime_error("Can't handle arrays of non-strings"));
	    outvp->push_back(sv->get_str());
	  }
	  (*mapp)[it->first] = *outvp;
	}
	break;
      case json_spirit::str_type:
	(*mapp)[it->first] = it->second.get_str();
	break;

      case json_spirit::bool_type:
	(*mapp)[it->first] = it->second.get_bool();
	break;

      case json_spirit::int_type:
	(*mapp)[it->first] = it->second.get_int64();
	break;

      case json_spirit::real_type:
	(*mapp)[it->first] = it->second.get_real();
	break;
      }
    }
    return true;
  } catch (runtime_error e) {
    ss << e.what();
    return false;
  }
}
