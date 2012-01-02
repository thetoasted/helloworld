<?php
/**
 * @file
 * waf_internal_service_feature.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function waf_internal_service_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
