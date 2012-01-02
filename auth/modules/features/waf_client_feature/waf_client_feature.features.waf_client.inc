<?php
/**
 * @file
 * waf_client_feature.features.waf_client.inc
 */

/**
 * Implementation of hook_waf_client_default_settings().
 */
function waf_client_feature_waf_client_default_settings() {
  $export = array();

  // Exported WAF Client setting: 
  $export['test_server'] = array(
    'site_host_url' => 'http://test_server.itv.com',
    'site_shared_key' => 'password1',
    'proxy_status' => '0',
    'enabled' => '1',
  );

  // Exported WAF Client setting: 
  $export['itvplayer'] = array(
    'site_host_url' => 'http://auth-svc/itvplayer',
    'site_shared_key' => 'password1',
    'proxy_status' => '0',
    'enabled' => '1',
  );


  // Exported WAF Client setting: 
  $export['paywizard.itv.com'] = array(
    'site_host_url' => 'http://paywizard.itv.com',
    'site_shared_key' => 'password1',
    'proxy_status' => '1',
    'enabled' => '1',
  );

  // Exported WAF Client setting: 
  $export['mercury.itv.com'] = array(
    'site_host_url' => 'http://mercury.itv.com',
    'site_shared_key' => 'password1',
    'proxy_status' => '0',
    'enabled' => '1',
  );

  return $export;
}
