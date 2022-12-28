.. _`Thread configuration`:

.. index:: Threads, Garbage, Liveliness, Deserialisation, Timed-event handling

********************
Thread configuration
********************

|var-project| creates several threads, each with a number of properties that can be 
controlled individually. These properties are:

- Stack size
- Scheduling class
- Scheduling priority

Each thread is uniquely named. To set the thread name set: 
:ref:`Threads/Thread[@name] <//CycloneDDS/Domain/Threads/Thread[@name]>`.
Any subset of threads can be given special properties. That is, anything not specified explicitly 
uses the default value.

The following are the built-in threads:

.. list-table::
  :align: left
  :widths: 20 80

  * - ``gc``
    - Garbage collector, which sleeps until garbage collection is requested for an entity, 
      at which point it starts monitoring the state of |var-project|. When it is safe to do so, 
      it pushes the entity through whatever state transitions are needed, ending with the 
      freeing of the memory.
  * - ``recv``
    - - Accepts incoming network packets from all sockets/ports.
      - Performs all protocol processing.
      - Queues (nearly) all protocol messages sent in response for handling by the timed-event thread.
      - Queues for delivery or, in special cases, delivers it directly to the data Readers.
  * - ``dq.builtins``
    - Processes all discovery data coming in from the network.
  * - ``lease``
    - Performs internal liveliness monitoring of |var-project|.
  * - ``tev``
    - Timed-event handling. Used for:
       - Periodic transmission of participant discovery and liveliness messages.
       - Transmission of control messages for reliable Writers and Readers (except those that have 
         their own timed-event thread)
       - Retransmitting of reliable data on request (except those that have their own timed-event thread). 
       - Handling of start-up mode to normal mode transition.

For each defined channel:

.. list-table::
  :align: left
  :widths: 20 80

  * - ``dq.channel-name``
    - Deserialisation and asynchronous delivery of all user data.
  * - ``tev.channel-name``
    - Channel-specific "timed-event" handling transmission of control messages for reliable Writers and Readers and retransmission of data on request. Channel-specific threads exist only if the configuration includes an element for it or if an auxiliary bandwidth limit is set for the channel.

When no channels are explicitly defined, there is one channel named *user*.
