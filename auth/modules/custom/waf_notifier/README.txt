INTRODUCTION
------------
Provides the capablility to notify the client servers (player.itv.com) that a user has been updated.
When a user is updated vai the user_service REST service WAF Notifer will create a job for each client
on its "notify_queue". A cron job will be run that will process the jobs from the queue and go and notify
the cleints.  The details for the client servers are provided by the WAF Client module.

INSTALLATION
------------
1. Copy waf_notify folder to the auth.itv.com modules directory
2. Enable the module using admin/modules or "drush en waf_notifier -y"
3. Eat biscuits
4. There is no spefici config for this module but the client settings can be seen at admin/config/system/waf_client
