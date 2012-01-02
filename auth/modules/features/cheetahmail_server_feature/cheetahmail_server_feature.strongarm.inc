<?php
/**
 * @file
 * cheetahmail_server_feature.strongarm.inc
 */

/**
 * Implementation of hook_strongarm().
 */
function cheetahmail_server_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cheetahmail_debug';
  $strongarm->value = 0;
  $export['cheetahmail_debug'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cheetahmail_login';
  $strongarm->value = 'sso-api';
  $export['cheetahmail_login'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cheetahmail_private_server_url';
  $strongarm->value = '';
  $export['cheetahmail_private_server_url'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cheetahmail_pwd';
  $strongarm->value = 'Drup4l2011';
  $export['cheetahmail_pwd'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cheetahmail_server_type';
  $strongarm->value = 'shared_server';
  $export['cheetahmail_server_type'] = $strongarm;

  return $export;
}
