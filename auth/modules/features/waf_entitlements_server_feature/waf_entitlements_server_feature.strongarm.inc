<?php
/**
 * @file
 * waf_entitlements_server_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function waf_entitlements_server_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'waf_control_production_crmid';
  $strongarm->value = 'itv';
  $export['waf_control_production_crmid'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'waf_control_production_password';
  $strongarm->value = 'uImH!8Fp5U@c';
  $export['waf_control_production_password'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'waf_control_production_server_host';
  $strongarm->value = 'das.itv.com';
  $export['waf_control_production_server_host'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'waf_control_production_server_path';
  $strongarm->value = 'services';
  $export['waf_control_production_server_path'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'waf_control_production_user';
  $strongarm->value = 'app@itv.com';
  $export['waf_control_production_user'] = $strongarm;

  return $export;
}
