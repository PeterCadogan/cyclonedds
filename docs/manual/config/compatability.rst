.. _`Compatibility issues with RTI`:

.. index:: Compatibility, RTI compatibility

.. include:: ../external-links.part.rst

========================
RTI compatibility issues
========================

In *lax* mode, most topic types should not have significant issues when working across a 
network.

When disposing of data, RTI DDS omits the serialised key value. Therefore, the Reader must 
use the embedded hash key value. In the strict modes, |var-project-short| requires a valid 
key value. In the relaxed mode, the Reader accepts the key hash value if it contains the 
key values in an unmangled form.

If an RTI DDS DataWriter disposes of an instance with a key where the serialised
representation is larger than 16 bytes, this problem is likely to occur. In
practice, the most likely cause is using a key as a string, either unbounded, or with a
maximum length larger than 11 bytes. See the |url::dds2.5| specification for details.

In *strict* mode, there is interoperation with RTI DDS, but at the cost of very high 
CPU and network load. This is caused by an endless loop of Heartbeats and AckNacks
between a reliable RTI DDS DataWriter and a reliable |var-project-short| data Reader. 
The reason for this is that when |var-project-short| informs the RTI Writer 
that it has received all data (using a valid AckNack message), the RTI Writer immediately 
publishes a message listing the range of available sequence numbers and requests an 
acknowledgment.

.. note::
    There is a difference in interpretation of the meaning of the
    "autodispose_unregistered_instances" QoS on the Writer. |var-project-short|
    aligns with |url::OpenSplice_link|.