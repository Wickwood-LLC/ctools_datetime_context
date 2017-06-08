<?php

/**
 * @file
 *
 * Plugin to provide a user_add_form context
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Datetime'),
  'description' => t('A datetime object'),
  'context' => 'ctools_datetime_context_create_datetime',
  'edit form' => 'ctools_datetime_context_datetime_settings_form',
  'defaults' => array(
    'year' => '',
    'month' => '',
    'day' => '',
    'hour' => '',
    'minute' => '',
    'second' => ''
  ),
  'keyword' => 'datetime',
  'context name' => 'datetime',
  'convert list' => array(),
  'convert' => 'ctools_datetime_context_datetime_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the user type this context.'),
  ),
);

$format_types = system_get_date_types();
foreach ($format_types as $type => $info) {
  $plugin['convert list'][$type] = $info['title'];
}

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ctools_datetime_context_create_datetime($empty, $data = NULL, $conf = FALSE) {
  static $creating = FALSE;
  $context = new ctools_context('datetime');
  $context->plugin = 'datetime';

  $contexts = ctools_get_contexts();

  if ($empty || ($creating)) {
    return $context;
  }
  $creating = TRUE;

  $datetime = new Datetime();
  $datetime->setDate(
    (int) (!empty($data['year']) ? $data['year'] : $datetime->format('Y')),
    (int) (!empty($data['month']) ? $data['month'] : $datetime->format('n')),
    (int) (!empty($data['day']) ? $data['day'] : $datetime->format('j'))
  );

  $datetime->setTime(
    (int) (!empty($data['hour']) ? $data['hour'] : $datetime->format('G')),
    (int) (!empty($data['minute']) ? $data['minute'] : $datetime->format('i')),
    (int) (!empty($data['second']) ? $data['second'] : $datetime->format('s'))
  );

  $context->data = $datetime;

  $creating = FALSE;
  return $context;
}

function ctools_datetime_context_datetime_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['year'] = array(
    '#title' => t('Year'),
    '#type' => 'textfield',
    '#default_value' => $conf['year'],
  );
  $form['month'] = array(
    '#title' => t('Month'),
    '#type' => 'textfield',
    '#default_value' => $conf['month'],
  );
  $form['day'] = array(
    '#title' => t('Day'),
    '#type' => 'textfield',
    '#default_value' => $conf['day'],
  );
  $form['hour'] = array(
    '#title' => t('Hour'),
    '#type' => 'textfield',
    '#default_value' => $conf['hour'],
  );
  $form['minute'] = array(
    '#title' => t('Minute'),
    '#type' => 'textfield',
    '#default_value' => $conf['minute'],
  );
  $form['second'] = array(
    '#title' => t('Second'),
    '#type' => 'textfield',
    '#default_value' => $conf['second'],
  );

  return $form;
}

function ctools_datetime_context_datetime_settings_form_submit($form, &$form_state) {
  $form_state['conf']['year'] = $form_state['values']['year'];
  $form_state['conf']['month'] = $form_state['values']['month'];
  $form_state['conf']['day'] = $form_state['values']['day'];
  $form_state['conf']['hour'] = $form_state['values']['hour'];
  $form_state['conf']['minute'] = $form_state['values']['minute'];
  $form_state['conf']['second'] = $form_state['values']['second'];
}

/**
 * Convert a context into a string.
 */
function ctools_datetime_context_datetime_convert($context, $type, $contexts) {
  $format_types = system_get_date_types();
  if (in_array($type, array_keys($format_types))) {
    return format_date($context->data->getTimestamp(), $type);
  }
  return '';
}
