<?php


$databases = array (
  'default' =>
  array (
    'default' =>
    array (
      'database'  => 'd7_auth',
      'host'      => 'localhost',
      'username'  => 'vagrant',
      'password'  => 'vagrant',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ),
);

$update_free_access = FALSE;
$drupal_hash_salt = '';
$base_url = 'http://localhost:8880/auth';

ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 0);
ini_set('session.cookie_path', '/auth');
# ini_set('pcre.backtrack_limit', 200000);
# ini_set('pcre.recursion_limit', 200000);

$conf['allow_authorize_operations'] = FALSE;
$conf['drupal_http_request_fails'] = FALSE;
$conf['error_level'] = '1';
$conf['file_temporary_path'] = '/srv/tmp';
$conf['nedstat_site_name'] = 'test';
$conf['adserver_current_site'] = 'TESTSITE';
$conf['apachesolr_default_environment'] = 'solr';
$conf['proxy_server'] = 'localhost';
$conf['proxy_port'] = '8080';
$conf['proxy_host'] = 'localhost:8080';




$conf['waf_api_geo_wsdl'] = 'http://g22ms17.itvbb.ads:55700/Services/GeoLocation.svc?wsdl';
$conf['esi_user_service_path'] = 'http://auth:8880/auth/api/internal_service/user/token.json';


# Varnish configuration.
$conf['cache'] = TRUE;
$conf['cache_backends'] = array('sites/all/modules/contrib/varnish/varnish.cache.inc');
$conf['cache_class_cache_page'] = 'VarnishCache';
$conf['page_cache_invoke_hooks'] = FALSE;
$conf['reverse_proxy'] = TRUE;
$conf['reverse_proxy_addresses'] = array('127.0.0.1');
$conf['varnish_control_terminal'] = '127.0.0.1:6082';


# Memcache configuration.
include_once('./includes/cache.inc');
include_once('./sites/all/modules/contrib/memcache/memcache.inc');
$conf['cache_backends'][] = 'sites/all/modules/contrib/memcache/memcache.inc';
$conf['cache_default_class'] = 'MemCacheDrupal';
$conf['cache_class_form'] = 'DrupalDatabaseCache';
$conf['memcache_key_prefix'] = 'auth-development';
$conf['memcache_servers'] = array('localhost:11211' => 'default');


