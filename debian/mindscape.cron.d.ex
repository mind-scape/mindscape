#
# Regular cron jobs for the mindscape package
#
0 4	* * *	root	[ -x /usr/bin/mindscape_maintenance ] && /usr/bin/mindscape_maintenance
