<?php

/**
 * 
 * @file Webservice method definitions and implementations for WAF SSO API
 * 
 * @see https://itvplc.jira.com/wiki/display/PROJECTS/Specification+of+SSO+API+for+trusted+third-parties
 * 
 */

function _waf_user_resource_definition() {
  $definition = array(
    'waf_user' => array(
      // external user API (retrieve) - we use index because the spec says the params are in the query string and
      // REST server will see this as an index page 
      // e.g. GET /api/user_service/user?sso_user_id=23423&service=paywizard.itv.com
      'index' => array(
        'help' => 'Retrieves a user for external services - GET 
          /api/user_service/user?sso_user_id=23423&service=paywizard.itv.com - Requires Digest',
        'callback' => '_waf_user_resource_index',
        'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
        'access callback' => '_waf_user_resource_access',
        'access arguments' => array('index'),
        'access arguments append' => FALSE,
        'args' => array(
          array(
            'name' => 'uid',
            'type' => 'int',
            'description' => 'The sso id of the user to retrieve.',
            'source' => array('param' => 'sso_user_id'),
            'optional' => TRUE,
            'default value' => 99,
          ),
          array(
            'name' => 'service',
            'type' => 'string',
            'description' => 'The calling service (used for digest).',
            'source' => array('param' => 'service'),
            'optional' => TRUE,
            'default value' => "default service",
          ),
        ),
      ),
      // internal user fetch e.g. 
      // GET /api/user_service/user/1 where 1 is an internal uid
      'retrieve' => array(
        'help' => 'Retrieves a user (for internal services) - 
          GET /api/user_service/user/1 where 1 is an internal uid',
        'callback' => '_waf_user_resource_retrieve',
        'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
        'access callback' => '_waf_user_resource_access',
        'access arguments' => array('retrieve'),
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'uid',
            'type' => 'int',
            'description' => 'The uid of the user to retrieve.',
            'source' => array('path' => '0'),
            'optional' => TRUE,            
          ),
        ),
      ),
      'actions' => array(
        // external authenticate api
        // POST /api/user_service/user/auth DATA sso_id and password
        'auth' => array(
          'help' => 'Confirms valid user credentials - POST /api/user_service/user/auth DATA sso_id and password
          	- Requires Digest',
          'callback' => '_waf_user_resource_auth',
          'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
          'access callback' => '_waf_user_resource_access',
          'access arguments' => array('auth'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'username',
              'type' => 'string',
              'description' => 'A valid username',
              'source' => array('data' => 'username'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'password',
              'type' => 'string',
              'description' => 'A valid password',
              'source' => array('data' => 'password'),
              'optional' => FALSE,
            ),
          ),
        ),
        // internal authenticate api
        // POST /api/user_service/user/auth DATA email and password and service_name
        'auth_client' => array(
          'help' => 'Confirms valid user credentials - POST /api/user_service/user/auth_client DATA email (= username)
          	 and password',
          'callback' => '_waf_user_resource_auth_client',
          'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
          'access callback' => '_waf_user_resource_access',
          'access arguments' => array('auth'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'username',
              'type' => 'string',
              'description' => 'A valid username',
              'source' => array('data' => 'username'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'password',
              'type' => 'string',
              'description' => 'A valid password',
              'source' => array('data' => 'password'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'service_name',
              'type' => 'string',
              'description' => 'A valid service_name',
              'source' => array('data' => 'service_name'),
              'optional' => FALSE,
            ),
          ),
        ),
        // TODO: document this method
        'validate' => array(
          'help' => 'Confirms valid user credentials',
          'callback' => '_waf_user_resource_validate',
          'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
          'access callback' => '_waf_user_resource_access',
          'access arguments' => array('auth'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'username',
              'type' => 'string',
              'description' => 'A valid username',
              'source' => array('data' => 'username'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'service_name',
              'type' => 'string',
              'description' => 'A valid service_name',
              'source' => array('data' => 'service_name'),
              'optional' => FALSE,
            ),
          ),
        ),
      ),
      // Create a user - Internal service
      // TODO: POST /api/user_service/user 
      // see comments _waf_user_resource_create below
      'create' => array(
        'help' => 'Create a user',
        'callback' => '_waf_user_resource_create',
        'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
        'access callback' => '_waf_user_resource_access',
        'access arguments' => array('create'),
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'data',
            'type' => 'struct',
            'description' => 'User details.',
            'source' => 'data',
            'optional' => FALSE,
          ),
        ),
      ),
      // Update a user - Internal service
      // is it PUT /api/user_service/user/sso_id
      // see comments _waf_user_resource_update below
      'update' => array(
        'help' => 'Update a user',
        'callback' => '_waf_user_resource_update',
        'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
        'access callback' => '_waf_user_resource_access',
        'access arguments' => array('update'),
        'access arguments append' => TRUE,
        'args' => array(
          array(
            'name' => 'sso_id',
            'type' => 'int',
            'description' => 'The uid of the user to retrieve.',
            'source' => array('path' => '0'),
            'optional' => FALSE,
          ),
          array(
            'name' => 'data',
            'type' => 'struct',
            'description' => 'User details.',
            'source' => 'data',
            'optional' => FALSE,
          ),
        ),
      ),

    ),
    // Check a digest - Internal service
    // TODO: document this service - 
    'waf_digest_check' => array(
      'create' => array(
        'help' => 'Check digest',
        'callback' => '_waf_user_resource_digest',
        'file' => array('type' => 'inc', 'module' => 'waf_user_resource', 'name' => 'includes/waf_user_resource'),
        'access callback' => '_waf_user_resource_access',
        'access arguments' => array('create'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'data',
              'type' => 'struct',
              'description' => 'Digest details.',
              'source' => 'data',
              'optional' => FALSE,
           ),
         ),
       ),
     ),
  );

  return $definition;
}



/**
 * INTERNAL ONLY Get user details.
 * No digest checking.
 * @param $uid
 *   UID of the user to be loaded.
 * This function also support the key word "token" instead of the $uid.
 * this supports the esi functionality for loading a user json object
 * into the page. The uid is obtained from the "cas_login_time" cookie
 * which decrypts to the  uid(sso_id)
 *
 * @return
 *   A user object.
 *
 * @see user_load()
 */
function _waf_user_resource_retrieve($uid) {
  wdd(array('uid' => $uid), 'waf user resource retrieve uid');


  if ( $uid == 'token' ) {
    $crypt_cookie =  isset($_COOKIE['cas_login_time'])  ? $_COOKIE['cas_login_time'] : NULL;
  wdd($crypt_cookie, "crypt_cookie");
    if ( is_null($crypt_cookie) ) {
  wdd("crypt_cookie NULL");
      $response = waf_get_rest_response(
       WAF_API_ERROR_USER_ID_NOT_FOUND,
       t('USER RETRIEVE: no crypt_cookie.'));
      return $response;
    }
  wdd("setting header");
  drupal_add_http_header('Cache-Control', 'public, max-age=86400');
  wdd("decrypting");
  $uid =  waf_api_decrypt($crypt_cookie);
  wdd($uid, "Token uid");
  }
  wdd($uid, "2uid");

  $account = is_numeric($uid) ? user_load($uid, TRUE) : NULL;

  if (empty($account)) {
    $response = waf_get_rest_response(
      WAF_API_ERROR_USER_ID_NOT_FOUND,
      t('USER RETRIEVE: There is no user with ID @uid.', array('@uid' => $uid)));
    return $response;
  }
  $response = waf_get_rest_response();
  // add basic fields
  $response->user = array(
    'id' => $account->uid,
    'email' => $account->mail,
  );
  // add fields added in account / fields
  // TODO: make this more robust - take into account multi-value fields etc.
  $lang = empty($account->language) ? LANGUAGE_NONE : $account->language;
  $fields = field_info_fields();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['bundles']['user'])) {
      $response->user[$field_name] = !empty($account->{$field_name}[$lang][0]['value']) ? 
        $account->{$field_name}[$lang][0]['value'] : 0;
    }
  } 
  return $response;
}


/**
 * Authorise a user using the specified credentials for paywizard/3rd parties.
 *
 * Note this will receive a plaintext password.
 *
 * @param $username
 *   Username to be logged in.
 * @param $password
 *   Password, must be plain text and not hashed.
 *
 * @return
 *   A valid session object.
 */
function _waf_user_resource_auth($sso_id, $password) {
wdd("_waf_user_resource_auth");
wdd(array('sso id' => $sso_id, 'password' => $password), 'waf user resource auth');
  //load account
  $account = user_load($sso_id);
wdd($account->name, 'account');
  //check if the user authenticates
  require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
  $checked = user_check_password($password, $account);
  if ( !$checked ) {
    $response = waf_get_rest_response(WAF_API_ERROR_BAD_USER_CREDENTIALS, t('USER AUTH: Bad username or password'));
wdd($response, 'response=');
    return $response;
  }
  // return a uid as a confirmation
  $response = waf_get_rest_response();
  $response->uid = $account->uid;
wdd($response, 'response=');
  return $response;
}

/**
 * Authorise a user using sso_id itv client sites i.e. player.
 *
 * Note this will receive a plaintext password.
 *
 * @param $username
 *   Username to be logged in.
 * @param $password
 *   Password, must be plain text and not hashed.
 *
 * @return
 *   A valid session object.
 */
function _waf_user_resource_auth_client($username, $password, $service_name) {
  wdd(array('username' => $username, 'password' => $password, 'service_name' => $service_name), 
    'waf user resource auth client');
  // check digest
  if (!waf_server_hash_check($username, $service_name)) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST,  t('Invalid request digest.'));
    return $response;
  }

  //ok lets authenticate the user
  $uid = user_authenticate($username, $password);
  if (!$uid) {
    $response = waf_get_rest_response(
      WAF_API_ERROR_BAD_USER_CREDENTIALS,
      t('USER AUTH: Bad username or password'));
    return $response;
  }
  $account = user_load($uid);
  wdd($account, 'account');
  //ok we are a good user lets get all the details and return them
  $response = waf_get_rest_response();
  $response->user = array(
    'id' => $account->uid,
    'name' => $account->name,
    'email' => $account->mail,
  );

  //see if a language has been set
  $lang = empty($account->language) ? LANGUAGE_NONE : $account->language;
  //get the user fields
  $fields = field_info_fields();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['bundles']['user'])) {
      $response->user[$field_name] = !empty($account->{$field_name}[$lang][0]['value']) ?
        $account->{$field_name}[$lang][0]['value'] : 0;
    }
  } 
  wdd($response, 'response');
  return $response;
}

/**
 * Access check callback for user resource.
 * External services rely on digest checking.  Access errors return error codes in the response so
 * we handle digest checks in the methods.
 * Internal services rely on network security
 */
function _waf_user_resource_access($op = 'retrieve', $args = array()) {
  return TRUE;
}

/**
 * Validate a user name has not been used.
 *
 * Note this will receive a plaintext password.
 *
 * @param $username
 *   Username to be validated 
 *
 * @param $service_name
 *   Clients service name 
 *
 * @return
 *   A valid session object.
 */
function _waf_user_resource_validate($username, $service_name) {
  wdd(array('username' => $username, 'service_name' => $service_name), "_waf_user_resource_validate");
  if ( is_null($username) ||  is_null($service_name) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, 
      t('not all of the required request parameters were present.'));
    return $response;
  }
  //check digest is ok
  if ( !waf_server_hash_check($username, $service_name) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, 
      t('Invalid request digest.'));
    return $response;
  }
  //set default user to not existing
  $user_exists = "no";
  //check if the user exists
  $results = db_query('SELECT uid FROM {users} WHERE name = :name', array(':name' => $username))->fetchAll();
  foreach ($results as $result) {
    $user_exists = "yes";
  }
  //create response
  $response = waf_get_rest_response(); 
  $response->user = array(
    'exists' => $user_exists,
  );
  wdd($response, "_waf_user_resource_validate response");
  return $response;
}

/**
 * Create a new user.
 *
 * Note this will receive a plaintext password.
 *
 * @param $data
 *   User array with account details basically from post data
 *
 * @return
 *   A sso_id.
 *
 *  Expect data structure these are sent as the payload of the POST request
 *  [email] => email@gmail.com
 *  [pass] => password 
 *  [service_name] => service_name
 *  [field_email_opt_in] => 0
 *  [field_first_name] => first_name
 *  [field_last_name] => last_name
 *  [field_user_title] => Mr
 *  [field_verified] => 1
 *
 * For this function to support extra functions all that is 
 * required is the key is the name of the field i.e. field_first_name 
 *
 */
function _waf_user_resource_create($data) {
  wdd(array('data' => $data), 'waf user resource create HIT');
error_log("_waf_user_resource_create");
  if ( is_null($data) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_REQUEST, 
      t('not all of the required request parameters were present.'));
    return $response;
  }
  wdd('checking hash');
  //check the hash is ok
  if ( !waf_server_hash_check($data['email'], $data['service_name'] ) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, t('Invalid request digest.'));
    return $response;
  }
  $account = array(
    'name' => $data['email'],
    'mail' => $data['email'],
    'init' => $data['email'],
    'pass' => $data['pass'],
    'status' => 1,
    'roles' => array(DRUPAL_AUTHENTICATED_RID => 'authenticated user'),
  );
  wdd('setup user');
  //get the lang to be used in getting correct fields
  $lang = empty($new_account->language) ? LANGUAGE_NONE : $account->language;
  //ok lets search through all the user fields
  $fields = field_info_fields();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['bundles']['user'])) {
      $account[$field_name][$lang][0]['value'] = $data[$field_name];
    }
  } 
  wdd('create user on control');
  // create the user on Irdeto control 
  if (module_exists('waf_control_user_sync')) {
    // lock the user table so we don't get out of sync waiting for a reply from irdeto
    wdd('control user sync');
    /*
     * perhaps we should be locking? TODO: sort this out
    if (!db_query('LOCK TABLES user')) {
      watchdog('waf_user_resource', 
      'Could not lock user table',
      array(),
      WATCHDOG_CRITICAL);
      wdd('no LOCK');
      return waf_get_rest_response(WAF_API_ERROR_INTERNAL_ERROR, 'Error creating account'); 
    }
    */
    // get the next user id
    $result = db_query('SELECT MAX(uid) as uid FROM {users}')->fetchAll();
    wdd($result, 'sync result');
    $sync_response = waf_control_user_sync_register($result[0]->uid + 1);
    wdd($sync_response, 'sync response');
    // check the user was succesfully created in control
    if (!is_object($sync_response) 
      || !isset($sync_response->headers['man-error-code'])
      || $sync_response->headers['man-error-code'] != 0) {
      watchdog('waf_user_resource', 
      	'Could not register user with Irdeto control',
        array(),
        WATCHDOG_ERROR);
      return waf_get_rest_response(WAF_API_ERROR_INTERNAL_ERROR, 'Error creating account');
    }
  }
  wdd('save the user');
  //now we save the user details 
  $new_account = user_save(drupal_anonymous_user(), $account);
  // Error if needed.
  if (is_object($new_account)) {
    $response = waf_get_rest_response(); 
    $response->user = array('sso_id' => $new_account->uid);
    wdd('user saved');
    return $response;
  } 
  else {
    $response = waf_get_rest_response(WAF_API_ERROR_INTERNAL_ERROR, 'Error creating account');
    wdd('user not saved'); 
    return $response;
  }
}

/**
 * this is a digest check for CAS and the creation of a new digest for CAS
 *
 * @param $data
 *   data array will hold the post array.
 *
 * @return
 *   A digest.
 */
function _waf_user_resource_digest($data) {
  wdd(array('data' => $data), "_waf_user_resource_digest");
  $service_ticket = empty($data['service_ticket']) ? '' : $data['service_ticket'];
  //$digest = empty($data['service_ticket']) ? '' : $data['service_ticket'];
  $sso_id = empty($data['SSO_User_id']) ? '' : $data['SSO_User_id'];
  $service_name = empty($data['Service_name']) ? '' : $data['Service_name'];
  $digest = empty($data['Digest']) ? '' : $data['Digest'];
  //$service_ticket = empty($data['Digest']) ? '' : $data['Digest'];

  $salt = $service_ticket . $sso_id;
  //check all the arguments are present
  if (is_null($service_ticket) ||  is_null($sso_id) || is_null($service_name) || is_null($digest) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_REQUEST, 
      t('not all of the required request parameters were present.'));
    wdd($response, "response1");
    return $response;
  }
  //check the digest and if ok create new one and return
  if (waf_server_hash_check_arg($service_ticket, $service_name, $digest) ) {
    //create new digest
    $client_digest = waf_server_hash_create($salt, $service_name);
    //return the digest
    $response = waf_get_rest_response(); 
    $response->digest = $client_digest;
    wdd($response, "response2");
    return $response;

  } 
  else {
    //there is something wrong with the digest
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, t('Invalid request digest.'));
    wdd($response, "response3");
    return $response;
  }
}

/**
 * Return user details formatted for external services (i.e. paywizard)
 * 
 * @param unknown_type $uid
 * SSO ID = uid on auth
 * @param unknown_type $service
 * Service name to use in the hash with the shared secret
 * @return $response
 * Response object
 */
function _waf_user_resource_index($uid, $service_name) {
  wdd(array('uid' => $uid, 'service_name' => $service_name), 'waf user resource index');
  $headers = getallheaders();
  $client_digest = empty($headers['Digest']) ? '' : $headers['Digest'];
  wdd($client_digest, 'incoming digest'); 
  //check all the arguments are present
  if ( is_null($uid) ||  is_null($service_name) || is_null($client_digest) ) {
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_REQUEST, t('Missing parameter.'));
    return $response;
  }
  // check digest
  if (!waf_server_hash_check($uid, $service_name ) ) {
    wdd('waf_server_hash_check failed');
    $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, t('Invalid request digest.'));
    return $response;
  }
  // load the user
  $account = is_numeric($uid) ? user_load($uid) : NULL;
  if (empty($account)) {
    $response = waf_get_rest_response(
      WAF_API_ERROR_USER_ID_NOT_FOUND,
      t('USER RETRIEVE: There is no user with ID @uid.', array('@uid' => $uid)));
    return $response;
  }
  $response = waf_get_rest_response();
  // add account fields
  //see if a language has been set
  $lang = empty($account->language) ? LANGUAGE_NONE : $account->language;  
  // TODO: define which fields get exposed on this service in the UI
  $response->user = array(
    'id' => $account->uid,
    'email' => $account->mail,
    'first_name' => empty($account->field_first_name) ? '' : $account->field_first_name[$lang][0]['value'],
    'last_name' => empty($account->field_last_name) ? '' : $account->field_last_name[$lang][0]['value'],
    'title' => empty($account->field_title) ? '' : $account->field_title[$lang][0]['value'],
  ); 
  //add the response digest
  drupal_add_http_header('Digest', waf_server_hash_create($response->user['last_name'], $service_name));
  return $response;
}

/**
 * Update a user details. This function works for two ways of updates.
 * 1. Update of the general fields
 * 2. Update of the user password
 * 
 * In both requests the email and service_name (see below) are required.
 *
 *  general update data structure
 *  [email] => testname@gmail.com
 *  [field_first_name] => first_name
 *  [field_last_name] => last_name
 *  [service_name] => service_name
 *  [name] => testname@gmail.com
 *
 *  password update data structure 
 *  [email] => testname@gmail.com
 *  [current_password] => current_password
 *  [new_password] => new_password
 *  [service_name] => service_name
 *
 * @param int $uid
 */

function _waf_user_resource_update($sso_id, $data) {
wdd($data, "_waf_user_resource_update=" . $sso_id);

 //ok check we have some data
 if ( is_null($data) ) {
wdd("ok1");
  $response = waf_get_rest_response(WAF_API_ERROR_INVALID_REQUEST,
    t('not all of the required request parameters were present.'));
  return $response;
 }

 //check the hash is ok
 if ( !waf_server_hash_check($sso_id, $data['service_name'] ) ) {
wdd("ok2");
  $response = waf_get_rest_response(WAF_API_ERROR_INVALID_DIGEST, t('Invalid request digest.'));
  return $response;
 }

 $account = user_load($sso_id);
 $lang = empty($account->language) ? LANGUAGE_NONE : $account->language;
 //check we loaded one ok
 if ( !is_object($account) ) {
wdd("ok3");
  $response = waf_get_rest_response(WAF_API_ERROR_INTERNAL_ERROR, 'Error loading account');
  return $response;
 }

 //ok now start creating an account to hold
 //the updated fields
 $new_account = array(
  'name' => $data['email'],
  'mail' => $data['email'],
 );
  //check if a password is being changed and check existing is valid
  if ( isset($data['current_password']) ) {
    require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
    $checked = user_check_password($data['current_password'], $account);
    if ( !$checked ) {
      $response = waf_get_rest_response(WAF_API_ERROR_BAD_USER_CREDENTIALS, t('USER AUTH: Bad username or password'));
      return $response;
    }
    $new_account['pass'] = $data['new_password'];
  }

  //update the fields
 $fields = field_info_fields();
 foreach ($fields as $field_name => $field) {
  if (!empty($field['bundles']['user'])) {
    if ( !empty($data[$field_name]) ) {
      $new_account[$field_name][$lang][0]['value'] = $data[$field_name];
    }
  }
 }

 //now we save the user details 
 $saved_account = user_save($account, $new_account);
 wdd($saved_account, 'waf user resource update user');
 // Error if needed.
 if ( is_object($saved_account) ) {

  $response = waf_get_rest_response();
  wdd($response, 'rest response');
  
  $response->user = array('sso_id' => $saved_account->uid);
  return $response;
 } 
 else {
  watchdog('waf notifier account update failed for account id: ' . $sso_id);
  wdd($sso_id, 'account update failed');
  $response = waf_get_rest_response(WAF_API_ERROR_INTERNAL_ERROR, 'Error creating account');
  return $response;
 }
}
