<?php

/**
 * @file
 * Plugin to provide an relationship handler for node from user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Datetime from strings'),
  'keyword' => 'datetime',
  'description' => t('Creates the datetime contexts from other string contexts.'),
  'required context' => array(
    'year' => new ctools_context_required(t('Year'), array('string')),
    'month' => new ctools_context_required(t('Month'), array('string')),
    'day' => new ctools_context_required(t('Day'), array('string')),
    'hour' => new ctools_context_required(t('Hour'), array('string')),
    'minute' => new ctools_context_required(t('Minute'), array('string')),
    'second' => new ctools_context_required(t('Second'), array('string')),
  ),
  'context' => 'ctools_datetime_context_add_datetime',
  'no ui' => FALSE,
);

/**
 * Return a new context based on an existing contexts.
 */
function ctools_datetime_context_add_datetime($contexts, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  // Just check only first source context.
  if (!empty($contexts[0]->empty)) {
    return ctools_context_create_empty('datetime', NULL);
  }

  $data = array();
  if (isset($contexts[0]) && empty($contexts[0]->empty)) {
    $data['year'] = $contexts[0]->data;
  }
  if (isset($contexts[1]) && empty($contexts[1]->empty)) {
    $data['month'] = $contexts[1]->data;
  }
  if (isset($contexts[2]) && empty($contexts[2]->empty)) {
    $data['day'] = $contexts[2]->data;
  }
  if (isset($contexts[3]) && empty($contexts[3]->empty)) {
    $data['hour'] = $contexts[3]->data;
  }
  if (isset($contexts[4]) && empty($contexts[4]->empty)) {
    $data['minute'] = $contexts[4]->data;
  }
  if (isset($contexts[5]) && empty($contexts[5]->empty)) {
    $data['second'] = $contexts[5]->data;
  }

  // Send it to ctools.
  return ctools_context_create('datetime', $data);
}
