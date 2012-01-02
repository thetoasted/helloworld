<?php
/**
 * @file
 * Admin functionality for WAF Client module.
 */

/**
 * Shows an overview of all site settings.
 */
function waf_client_settings_view() {
  $rows = array();
  $header = array(
    array('data' => t('Service Name'), 'field' => 'waf.service_name', 'sort' => 'asc'),
    array('data' => t('Host URL'), 'field' => 'waf.site_host_url'),
//    array('data' => t('Shared Key'), 'field' => 'waf.site_shared_key'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );

  $sites = db_select('waf_client_settings', 'waf', array('target' => 'slave'))
    ->fields('waf', drupal_schema_fields_sql('waf_client_settings'))
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->limit(30)
    ->orderByHeader($header)
    ->execute();

  foreach ($sites as $site) {
    $rows[] = array(
      check_plain($site->service_name),
      check_plain($site->site_host_url),
//      check_plain(truncate_utf8($site->site_shared_key, 32, FALSE, TRUE)),
      l(t('edit'), "admin/config/system/waf_client/manage/{$site->service_name}/edit"),
      l(t('delete'), "admin/config/system/waf_client/manage/{$site->service_name}/delete"),
    );
  }

  $build['waf_client_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No sites available. <a href="@link">Add site setting</a>.', array('@link' => url('admin/config/system/waf_client/add'))),
  );
  $build['waf_client_pager'] = array('#theme' => 'pager');

  return $build;
}

/**
 * Multi-purpose admin form for WAF Client add/ edit settings.
 */
function waf_client_settings($form, &$form_state, $client_settings = NULL) {
  $form['waf']['#tree'] = TRUE;
  $form['old_service_name'] = array(
    '#type' => 'value',
    '#value' => isset($client_settings->service_name) ? $client_settings->service_name : NULL,
  );
  $form['waf']['service_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Name'),
    '#description' => t('Enter a unique Service Name'),
    '#default_value' => isset($client_settings->service_name) ? $client_settings->service_name : '',
    '#required' => TRUE,
    '#weight' => 1
  );
  $form['waf']['site_host_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('Client Host URL'),
    '#default_value' => isset($client_settings->site_host_url) ? $client_settings->site_host_url : '',
    '#required' => TRUE,
    '#weight' => 2
  );
  $form['waf']['site_shared_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Shared private key'),
    '#description' => t('Private key to be used in digest between WAF and client site.'),
    '#default_value' => isset($client_settings->site_shared_key) ? $client_settings->site_shared_key : '',
    '#required' => TRUE,
    '#weight' => 3
  );
  $form['waf']['proxy_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is proxy required'),
    '#description' => t('If the client is external to the ITV network we will need to proxy out to it.'),
    '#default_value' => isset($client_settings->proxy_status) ? $client_settings->proxy_status : '0',
    '#required' => FALSE,
    '#weight' => 4
  );

  $form['waf']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled the client'),
    '#description' => t('Enable or disable the client.'),
    '#default_value' => isset($client_settings->enabled) ? $client_settings->enabled : '1',
    '#required' => FALSE,
    '#weight' => 4
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#href' => isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/system/waf_client',
    '#title' => t('Cancel'),
  );

  return $form;
}

/**
 * Validation callback for the waf_client_settings form.
 */
function waf_client_settings_validate($form, &$form_state) {
  $clients = waf_client_get_clients();
  if (isset($clients[$form_state['values']['waf']['service_name']])) {
    form_set_error('waf][service_name', t('Error Service Name must be unique.'));
  }
}

/**
 * Submit callback for the waf_client_settings form.
 */
function waf_client_settings_submit($form, &$form_state) {
  if (isset($form_state['values']['old_service_name'])) {
    $client_settings = waf_client_client_load($form_state['values']['old_service_name']);
    db_update('waf_client_settings')
      ->fields($form_state['values']['waf'])
      ->condition('service_name', $client_settings->service_name)
      ->execute();
    drupal_set_message(t('The settings for site %name have been updated.', array('%name' => $client_settings->service_name)));
  }
  else {
    drupal_write_record('waf_client_settings', $form_state['values']['waf']);
    drupal_set_message(t('The settings for site %name have been created.', array('%name' => $form_state['values']['waf']['service_name'])));
  }
  waf_client_site_settings_reset();
  $form_state['redirect'] = 'admin/config/system/waf_client';
}

/**
 * Callback to delete a sites' settings.
 */
function waf_client_settings_delete($form, &$form_state, $client_settings) {
  $form['service_name'] = array(
    '#type' => 'value',
    '#value' => $client_settings->service_name,
  );
  return confirm_form(
    $form,
    t('Are you sure you want to delete the settings for site %name?', array('%name' => $client_settings->service_name)),
    'admin/config/system/waf_client',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit callback for the waf_client_settings_delete form.
 */
function waf_client_settings_delete_submit($form, &$form_state) {
  $client_settings = waf_client_client_load($form_state['values']['service_name']);
  db_delete('waf_client_settings')
    ->condition('service_name', $client_settings->service_name)
    ->execute();
  drupal_set_message(t('The settings for site %name have been deleted.', array('%name' => $client_settings->service_name)));
  waf_client_site_settings_reset();
  $form_state['redirect'] = 'admin/config/system/waf_client';
}
