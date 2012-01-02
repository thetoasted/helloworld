<?php
/**
 * @file
 * cheetahmail_server_feature.rules_defaults.inc
 */

/**
 * Implementation of hook_default_rules_configuration().
 */
function cheetahmail_server_feature_default_rules_configuration() {
  $items = array();
  $items['rules_cheetahmail_unsubscribe_all'] = entity_import('rules_config', '{ "rules_cheetahmail_unsubscribe_all" : {
      "LABEL" : "CheetahMail Unsubscribe all",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "cheetahmail" ],
      "ON" : [ "user_delete" ],
      "DO" : [
        { "cheetahmail_call_api" : {
            "type" : "setuser1",
            "query_params" : "unsub=*\\r\\nemail=[account:mail]\\r\\naid=2075638158\\r\\n"
          }
        }
      ]
    }
  }');
  $items['rules_cheetahmail_update_user_details'] = entity_import('rules_config', '{ "rules_cheetahmail_update_user_details" : {
      "LABEL" : "CheetahMail update user details",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "CheetahMail" ],
      "REQUIRES" : [ "rules", "cheetahmail" ],
      "ON" : [ "user_update" ],
      "DO" : [
        { "cheetahmail_call_api" : {
            "type" : "setuser1",
            "query_params" : "aid=2075638158\r\nemail=[account-unchanged:mail]\r\nFNAME=[account:field-first-name]\r\nLNAME=[account:field-last-name]\r\nOVER18=SSO"
          }
        }
      ]
    }
  }');
  $items['rules_cheetahmail_welcome_email'] = entity_import('rules_config', '{ "rules_cheetahmail_welcome_email" : {
      "LABEL" : "CheetahMail welcome email",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "cheetahmail" ],
      "ON" : [ "user_insert" ],
      "IF" : [ { "data_is_empty" : { "data" : [ "account:field-email-opt-in" ] } } ],
      "DO" : [
        { "cheetahmail_call_api" : {
            "type" : "ebmtrigger1",
            "query_params" : "aid=2075638158\r\nemail=[account:mail]\r\nsub=2075661100\r\nfsub=2075661100|2075638166\r\neid=184507\r\nRCODE=sso\r\nFNAME=[account:field-first-name]\r\nLNAME=[account:field-last-name]\r\nOVER18=SSO"
          }
        }
      ]
    }
  }');
  $items['rules_cm_set_user'] = entity_import('rules_config', '{ "rules_cm_set_user" : {
      "LABEL" : "CheetahMail set user",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "cheetahmail" ],
      "ON" : [ "user_insert" ],
      "IF" : [
        { "NOT data_is_empty" : { "data" : [ "account:field-email-opt-in" ] } }
      ],
      "DO" : [
        { "cheetahmail_call_api" : {
            "type" : "setuser1",
            "query_params" : "aid=2075638158\r\nemail=[account:mail]\r\nsub=2075661100\r\nfsub=2075661100|2075638166\r\ne=184508\r\nRCODE=sso\r\nFNAME=[account:field-first-name]\r\nLNAME=[account:field-last-name]\r\nOVER18=SSO"
          }
        }
      ]
    }
  }');
  return $items;
}
