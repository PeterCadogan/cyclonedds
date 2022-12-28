.. _`Conformance modes`:

.. index:: Conformance, Interoperability

=================
Conformance modes
=================

This sets the level of standards conformance for this instance of the |var-project|
Service. Stricter conformance typically means less interoperability with other implementations.
|var-project| operates in one of three modes:

- *lax*
  
  In *lax* mode (default), the |var-project| can accept and transmit some invalid messages.

- *pedantic*
  
  Conforms to the specification.

- *strict*
  
  Attempts to follow the *intent* of the specification while staying close to the 
  letter of it.

To set the conformance mode, use:
:ref:`Compatibility/StandardsConformance <//CycloneDDS/Domain/Compatibility/StandardsConformance>`.

.. note::

  If there are two |var-project| processes with different compliancy modes, the one in 
  the stricter mode will complain about messages sent by the one in the less strict mode.
