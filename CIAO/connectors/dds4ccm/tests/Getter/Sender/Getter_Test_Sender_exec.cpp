// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.3
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

#include "Getter_Test_Sender_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

namespace CIAO_Getter_Test_Sender_Impl
{
  /**
   * Pulse generator
   */
  pulse_Generator::pulse_Generator (Sender_exec_i &callback)
    : pulse_callback_ (callback)
  {
  }

  int
  pulse_Generator::handle_timeout (const ACE_Time_Value &, const void *)
  {
    this->pulse_callback_.tick ();
    return 0;
  }

  /**
   * Facet Executor Implementation Class: info_out_connector_status_exec_i
   */

  info_out_connector_status_exec_i::info_out_connector_status_exec_i (
        ::Getter_Test::CCM_Sender_Context_ptr ctx,
        Sender_exec_i &callback)
    : ciao_context_ (
        ::Getter_Test::CCM_Sender_Context::_duplicate (ctx))
      , callback_ (callback)
  {
  }

  info_out_connector_status_exec_i::~info_out_connector_status_exec_i (void)
  {
  }

  // Operations from ::CCM_DDS::ConnectorStatusListener

  void
  info_out_connector_status_exec_i::on_inconsistent_topic (::DDS::Topic_ptr /* the_topic */,
  const ::DDS::InconsistentTopicStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_connector_status_exec_i::on_requested_incompatible_qos (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::RequestedIncompatibleQosStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_connector_status_exec_i::on_sample_rejected (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::SampleRejectedStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_connector_status_exec_i::on_offered_deadline_missed (::DDS::DataWriter_ptr /* the_writer */,
  const ::DDS::OfferedDeadlineMissedStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_connector_status_exec_i::on_offered_incompatible_qos (::DDS::DataWriter_ptr /* the_writer */,
  const ::DDS::OfferedIncompatibleQosStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_connector_status_exec_i::on_unexpected_status (::DDS::Entity_ptr /* the_entity */,
  ::DDS::StatusKind status_kind)
  {
    if (status_kind == ::DDS::PUBLICATION_MATCHED_STATUS)
      {
        this->callback_.start ();
      }
  }

  /**
   * Component Executor Implementation Class: Sender_exec_i
   */

  Sender_exec_i::Sender_exec_i (void)
    : keys_ (5)
      , iterations_ (10)
      , done_ (false)
      , ccm_activated_ (false)
      , last_iter_ (1)
  {
    this->ticker_ = new pulse_Generator (*this);
  }

  Sender_exec_i::~Sender_exec_i (void)
  {
  }

  // Supported operations and attributes.
  ACE_Reactor*
  Sender_exec_i::reactor (void)
  {
    ACE_Reactor* reactor = 0;
    ::CORBA::Object_var ccm_object =
      this->ciao_context_->get_CCM_object();
    if (! ::CORBA::is_nil (ccm_object.in ()))
      {
        ::CORBA::ORB_var orb = ccm_object->_get_orb ();
        if (! ::CORBA::is_nil (orb.in ()))
          {
            reactor = orb->orb_core ()->reactor ();
          }
      }
    if (reactor == 0)
      {
        throw ::CORBA::INTERNAL ();
      }
    return reactor;
  }

  // Component attributes and port operations.
  void
  Sender_exec_i::start_timeout_tests (void)
  {
    GetInvoker_var invoker =
      this->ciao_context_->get_connection_invoke_getter ();

    invoker->start_timeout_get_one ();
    invoker->start_timeout_get_many ();
  }

  void
  Sender_exec_i::write_many (void)
  {
    ::Getter_Test::GetterTestConnector::Writer_var writer =
      this->ciao_context_->get_connection_info_write_data ();
    GetInvoker_var invoker =
      this->ciao_context_->get_connection_invoke_getter ();


    //Prepare the samples.
    GetterTestSeq write_many (this->keys_ * this->iterations_);
    write_many.length (this->keys_ * this->iterations_);
    // since the test for get_one already writes samples to DDS with
    // key=KEY_1 we start with key = 2 when writing many samples.
    for (CORBA::UShort key = 2; key < this->keys_ + 2; ++key)
      {
        GetterTest new_key;
        char tmp[7];
        ACE_OS::sprintf (tmp, "KEY_%d", key);
        new_key.key = CORBA::string_dup(tmp);
        for (CORBA::UShort iter = 1; iter < this->iterations_ + 1; ++iter)
          {
            new_key.iteration = iter;
            write_many[(iter - 1) + ((key - 2) * 10)] = new_key;
          }
      }
    try
      {
        // Inform the receiver that the sender has written many
        // samples to DDS.
        invoker->start_get_many (this->keys_, this->iterations_);
        // Wait a while before writing the samples.
        ACE_Time_Value tv (2, 0);
        ACE_OS::sleep (tv);
        // Now start writing.
        writer->write_many (write_many);
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("write_many : written <%u> samples\n"),
              write_many.length ()));
      }
    catch (const CCM_DDS::InternalError& ex)
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: Internal Error ")
                    ACE_TEXT ("while write many writer info: index <%d> - retval <%d>\n"),
                      ex.index, ex.error_code));
      }
  }

  void
  Sender_exec_i::start (void)
  {
    // Start can be called more than once...
    if (!this->done_ && this->ccm_activated_)
      {
        this->done_ = true;
        start_timeout_tests ();
        if (this->reactor ()->schedule_timer (
                    this->ticker_,
                    0,
                    ACE_Time_Value (0, 500000),
                    ACE_Time_Value (0, 500000)) == -1)
          {
            ACE_ERROR ((LM_ERROR, ACE_TEXT ("Sender_exec_i::start : ")
                                  ACE_TEXT ("Error scheduling timer")));
          }
      }
  }

  void
  Sender_exec_i::tick (void)
  {
    ::Getter_Test::GetterTestConnector::Writer_var writer =
      this->ciao_context_->get_connection_info_write_data ();
    ::Getter_Test::GetterFixedConnector::Writer_var fixed =
      this->ciao_context_->get_connection_info_fixed_data ();
    ::GetInvoker_var invoker =
      this->ciao_context_->get_connection_invoke_getter ();

    if (this->last_iter_ <= this->iterations_)
      {
        GetterFixed  fixed_key;
        GetterTest *new_key = new GetterTest;
        new_key->key = CORBA::string_dup ("KEY_1");
        fixed_key.key = 1;
        // Inform the receiver that this class (as the sender) is about to
        // write samples to DDS.
        invoker->start_get_one ("KEY_1", 1, last_iter_);

        new_key->iteration = last_iter_;
        fixed_key.iteration = last_iter_;

        ACE_Time_Value tv (0, 50000);
        ACE_OS::sleep (tv);

        writer->write_one (*new_key, ::DDS::HANDLE_NIL);
        fixed->write_one (fixed_key, ::DDS::HANDLE_NIL);
        ACE_DEBUG ((LM_DEBUG, "Written keys <%C> and <%u> with <%d>\n",
                    new_key->key.in (), fixed_key.key, last_iter_));

        ++last_iter_;
        delete new_key;
    }
   else
    {
      // Stop the timer at forehand.
      this->reactor ()->cancel_timer (this->ticker_);
      // Perform the last test.
      this->write_many ();
    }
  }

  ::CCM_DDS::CCM_ConnectorStatusListener_ptr
  Sender_exec_i::get_info_out_connector_status (void)
  {
    if ( ::CORBA::is_nil (this->ciao_info_out_connector_status_.in ()))
      {
        info_out_connector_status_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          info_out_connector_status_exec_i (
            this->ciao_context_.in (),
            *this),
            ::CCM_DDS::CCM_ConnectorStatusListener::_nil ());

          this->ciao_info_out_connector_status_ = tmp;
      }

    return
      ::CCM_DDS::CCM_ConnectorStatusListener::_duplicate (
        this->ciao_info_out_connector_status_.in ());
  }

  ::CORBA::UShort
  Sender_exec_i::keys (void)
  {
    return this->keys_;
  }

  void
  Sender_exec_i::keys (
    const ::CORBA::UShort keys)
  {
    this->keys_ = keys;
  }

  ::CORBA::UShort
  Sender_exec_i::iterations (void)
  {
    return this->iterations_;
  }

  void
  Sender_exec_i::iterations (
    const ::CORBA::UShort iterations)
  {
    this->iterations_ = iterations;
  }

  // Operations from Components::SessionComponent.

  void
  Sender_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::Getter_Test::CCM_Sender_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  Sender_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  Sender_exec_i::ccm_activate (void)
  {
    this->ccm_activated_ = true;
  }

  void
  Sender_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  Sender_exec_i::ccm_remove (void)
  {
    this->reactor ()->cancel_timer (this->ticker_);
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Sender_exec_i::stop : Timer canceled.\n")));
    delete this->ticker_;
  }

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Getter_Test_Sender_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Sender_exec_i);

    return retval;
  }
}
