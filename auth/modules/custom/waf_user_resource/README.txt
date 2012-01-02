WAF User Resource

Provides a Services 7.x-3.x Resource for the WAF project.  Designed to be used with the REST server provided with Services
this  module should also work with any other server but as yet that functionality is untested.

Responses are in a custom XML format.

Responses always contain an error tags which are empty if there is no error.

METHODS

* Paths may be aliased in services config - the paths below are module defaults *

User Retrieve

GET /{endpoint}/waf_user/{uid}
Returns XML given a Valid User ID in {uid}

Example FAIL response
<Response xmlns="http://hobnob.loc/api/user_service/user/99">
   <error>
      <error_code>1</error_code>
      <error_message>USER RETRIEVE: There is no user with ID 99.</error_message>
   </error>
</Response>

Example SUCCESS response
<Response xmlns="http://hobnob.loc/api/user_service/user/1">
   <error>
      <error_code/>
      <error_message/>
   </error>
   <user>
      <email>noone@nowhere.com</email>
      <id>1</id>
   </user>
</Response>

User Auth

POST /{endpoint}/waf_user/auth/ PARAMS (url encoded in POST body) username, password

Returns XML given a Valid username and password in POST

Example SUCCESS response:
<Response xmlns="http://hobnob.loc/api/user_service/user/auth">
   <error>
      <error_code/>
      <error_message/>
   </error>
   <uid>9</uid>
</Response>

Example FAIL response
<Response xmlns="http://hobnob.loc/api/user_service/user/auth">
   <error>
      <error_code>2</error_code>
      <error_message>USER AUTH: Bad username or password</error_message>
   </error>
</Response>

---- Tests ----
Simple tests are included for the Methods, based on the REST server tests in Services module
Also included is a test project for SOAP UI v.4

