// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html


ACE_INLINE
void
POA_CORBA::ConstructionPolicy::_get_policy_type_skel (
    TAO_ServerRequest & server_request,
    void * servant_upcall,
    void * servant
    ACE_ENV_ARG_DECL
  )
{
  POA_CORBA::Policy * const impl = static_cast<POA_CORBA::ConstructionPolicy *> (servant);
  POA_CORBA::Policy::_get_policy_type_skel (
      server_request,
      servant_upcall,
      impl
      ACE_ENV_ARG_PARAMETER
    );
}

// TAO_IDL - Generated from
// be\be_interface.cpp:1859

ACE_INLINE
void
POA_CORBA::ConstructionPolicy::copy_skel (
    TAO_ServerRequest & server_request,
    void * servant_upcall,
    void * servant
    ACE_ENV_ARG_DECL
  )
{
  POA_CORBA::Policy * const impl = static_cast<POA_CORBA::ConstructionPolicy *> (servant);
  POA_CORBA::Policy::copy_skel (
      server_request,
      servant_upcall,
      impl
      ACE_ENV_ARG_PARAMETER
    );
}

// TAO_IDL - Generated from
// be\be_interface.cpp:1859

ACE_INLINE
void
POA_CORBA::ConstructionPolicy::destroy_skel (
    TAO_ServerRequest & server_request,
    void * servant_upcall,
    void * servant
    ACE_ENV_ARG_DECL
  )
{
  POA_CORBA::Policy * const impl = static_cast<POA_CORBA::ConstructionPolicy *> (servant);
  POA_CORBA::Policy::destroy_skel (
      server_request,
      servant_upcall,
      impl
      ACE_ENV_ARG_PARAMETER
    );
}

// TAO_IDL - Generated from
// be\be_interface.cpp:1244

ACE_INLINE void
POA_CORBA::_TAO_ConstructionPolicy_Direct_Proxy_Impl::_get_policy_type (
    TAO_Abstract_ServantBase *servant,
    TAO::Argument ** args,
    int num_args
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  POA_CORBA::_TAO_Policy_Direct_Proxy_Impl::_get_policy_type (
      servant,
      args,
      num_args
      ACE_ENV_ARG_PARAMETER
    );
}


// TAO_IDL - Generated from
// be\be_interface.cpp:1244

ACE_INLINE void
POA_CORBA::_TAO_ConstructionPolicy_Direct_Proxy_Impl::copy (
    TAO_Abstract_ServantBase *servant,
    TAO::Argument ** args,
    int num_args
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  POA_CORBA::_TAO_Policy_Direct_Proxy_Impl::copy (
      servant,
      args,
      num_args
      ACE_ENV_ARG_PARAMETER
    );
}


// TAO_IDL - Generated from
// be\be_interface.cpp:1244

ACE_INLINE void
POA_CORBA::_TAO_ConstructionPolicy_Direct_Proxy_Impl::destroy (
    TAO_Abstract_ServantBase *servant,
    TAO::Argument ** args,
    int num_args
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  POA_CORBA::_TAO_Policy_Direct_Proxy_Impl::destroy (
      servant,
      args,
      num_args
      ACE_ENV_ARG_PARAMETER
    );
}

