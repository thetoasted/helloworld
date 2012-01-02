<?php
/**
 * @file
 * cheetahmail_server_feature.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function cheetahmail_server_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
