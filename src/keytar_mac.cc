
#ifdef __APPLE__

#include "keytar.h"

#include <Security/Security.h>

namespace keytar {

bool AddPassword(const std::string& service,
                 const std::string& account,
                 const std::string& password) {
  OSStatus status = SecKeychainAddGenericPassword(NULL,
                                                  service.length(),
                                                  service.data(),
                                                  account.length(),
                                                  account.data(),
                                                  password.length(),
                                                  password.data(),
                                                  NULL);
  return status == errSecSuccess;
}

bool GetPassword(const std::string& service,
                 const std::string& account,
                 std::string* password) {
  void *data;
  UInt32 length;
  OSStatus status = SecKeychainFindGenericPassword(NULL,
                                                  service.length(),
                                                  service.data(),
                                                  account.length(),
                                                  account.data(),
                                                  &length,
                                                  &data,
                                                  NULL);
  if (status != errSecSuccess)
    return false;

  *password = std::string(reinterpret_cast<const char*>(data), length);
  SecKeychainItemFreeContent(NULL, data);
  return true;
}

bool DeletePassword(const std::string& service, const std::string& account) {
  SecKeychainItemRef item;
  OSStatus status = SecKeychainFindGenericPassword(NULL,
                                                   service.length(),
                                                   service.data(),
                                                   account.length(),
                                                   account.data(),
                                                   NULL,
                                                   NULL,
                                                   &item);
  if (status != errSecSuccess)
    return false;

  status = SecKeychainItemDelete(item);
  CFRelease(item);
  return status == errSecSuccess;
}

bool FindPassword(const std::string& service, std::string* password) {
  SecKeychainItemRef item;
  void *data;
  UInt32 length;

  OSStatus status = SecKeychainFindGenericPassword(NULL,
                                                   service.length(),
                                                   service.data(),
                                                   0,
                                                   NULL,
                                                   &length,
                                                   &data,
                                                   &item);
  if (status != errSecSuccess)
    return false;

  *password = std::string(reinterpret_cast<const char*>(data), length);
  SecKeychainItemFreeContent(NULL, data);
  CFRelease(item);
  return true;
}

// ---------------------------------------------------------------------
// Internet passwords

bool AddInternetPassword(const std::string& servername,
			 const std::string& account,
			 int port,
			 const std::string& password) {

  OSStatus status = SecKeychainAddInternetPassword
    (NULL,			// keychain
     servername.length(),
     servername.data(),
     0, NULL,			// securityDomain
     account.length(),
     account.data(),
     0, NULL,			// path
     port,
     kSecProtocolTypeAny,
     kSecAuthenticationTypeAny,
     password.length(),
     password.data(),
     NULL);

  return status == errSecSuccess;
}

bool GetInternetPassword(const std::string& servername,
			 const std::string& account,
			 int port,
			 std::string* password) {

  void *data;
  UInt32 length;

  OSStatus status = SecKeychainFindInternetPassword
    (NULL,			// keychain
     servername.length(),
     servername.data(),
     0, NULL,			// securityDomain
     account.length(),
     account.data(),
     0, NULL,			// path
     port,
     kSecProtocolTypeAny,
     kSecAuthenticationTypeAny,
     &length,
     &data,
     NULL);

  if (status != errSecSuccess)
    return false;

  *password = std::string(reinterpret_cast<const char*>(data), length);
  SecKeychainItemFreeContent(NULL, data);
  return true;
}

bool DeleteInternetPassword(const std::string& servername,
			    const std::string& account,
			    int port) {

  SecKeychainItemRef item;

  OSStatus status = SecKeychainFindInternetPassword
    (NULL,			// keychain
     servername.length(),
     servername.data(),
     0, NULL,			// securityDomain
     account.length(),
     account.data(),
     0, NULL,			// path
     port,
     kSecProtocolTypeAny,
     kSecAuthenticationTypeAny,
     NULL,
     NULL,
     &item);

  if (status != errSecSuccess)
    return false;

  status = SecKeychainItemDelete(item);
  CFRelease(item);
  return status == errSecSuccess;
}

bool FindInternetPassword(const std::string& servername,
			  int port,
			  std::string* password) {

  SecKeychainItemRef item;
  void *data;
  UInt32 length;

  OSStatus status = SecKeychainFindInternetPassword
    (NULL,			// keychain
     servername.length(),
     servername.data(),
     0, NULL,			// securityDomain
     0, NULL,			// account
     0, NULL,			// path
     port,
     kSecProtocolTypeAny,
     kSecAuthenticationTypeAny,
     &length,
     &data,
     &item);

  if (status != errSecSuccess)
    return false;

  *password = std::string(reinterpret_cast<const char*>(data), length);
  SecKeychainItemFreeContent(NULL, data);
  CFRelease(item);
  return true;
}

}  // namespace keytar

#endif
