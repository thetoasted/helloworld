<?php
/**
 * @file
 * waf_user_service_feature.services.inc
 */

/**
 * Implementation of hook_default_services_endpoint().
 */
function waf_user_service_feature_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'waf_user_service';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'api/user_service';
  $endpoint->authentication = array();
  $endpoint->server_settings = array(
    'rest_server' => array(
      'formatters' => array(
        'xml' => TRUE,
        'json' => FALSE,
        'php' => FALSE,
        'jsonp' => FALSE,
        'yaml' => FALSE,
        'bencode' => FALSE,
        'rss' => FALSE,
      ),
      'parsers' => array(
        'application/x-www-form-urlencoded' => TRUE,
        'application/x-yaml' => TRUE,
        'application/json' => TRUE,
        'application/vnd.php.serialized' => TRUE,
        'multipart/form-data' => TRUE,
        'application/xml' => TRUE,
      ),
    ),
  );
  $endpoint->resources = array(
    'waf_user' => array(
      'alias' => 'user',
      'operations' => array(
        'index' => array(
          'enabled' => 1,
        ),
        'retrieve' => array(
          'enabled' => 1,
        ),
        'create' => array(
          'enabled' => 1,
        ),
        'update' => array(
          'enabled' => 1,
        ),
      ),
      'actions' => array(
        'auth' => array(
          'enabled' => 1,
        ),
        'auth_client' => array(
          'enabled' => 1,
        ),
        'validate' => array(
          'enabled' => 1,
        ),
      ),
    ),
    'waf_digest_check' => array(
      'alias' => 'digest',
      'operations' => array(
        'create' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 1;
  $export['waf_user_service'] = $endpoint;

  return $export;
}
