// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO/orbsvcs/tests/Interoperable_Naming/
//
// = FILENAME
//    client.cpp
//
// = DESCRIPTION
//     This implements a simple CORBA client for the
//     CosNaming::NamingContextExt example
//
// = AUTHORS
//     Priyanka Gontla <pgontla@ece.uci.edu>
//
//
// ============================================================================

#include "ncontextext_client_i.h"

int main (int argc, char *argv [])
{

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {

      NContextExt_Client_i client;

      if (client.init (argc, argv) == -1)
        return 1;
      else
        {
          return client.run (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "client");
      ACE_RE_THROW;
    }
  ACE_ENDTRY;

  return 0;
}
