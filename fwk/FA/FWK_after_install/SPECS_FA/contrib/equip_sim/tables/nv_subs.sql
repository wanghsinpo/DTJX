SQL "open sub nv1 to variables sqlproc=nv_update_log insert update delete * where varclass='ECV'"
SQL "open sub nv2 to reports sqlproc=nv_update_log insert update delete *"
SQL "open sub nv3 to alarms sqlproc=nv_update_log insert update delete is_reported"
SQL "open sub nv4 to event_reports sqlproc=nv_update_log insert update delete *"

