/*****************************************************************
|
|   Platinum - UPnP Helper
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and 
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
| licensing@plutinosoft.com
|  
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc., 
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
****************************************************************/

#ifndef _PLT_UPNP_HELPER_H_
#define _PLT_UPNP_HELPER_H_

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Neptune.h"

/*----------------------------------------------------------------------
|   NPT_StringFinder
+---------------------------------------------------------------------*/
/**
 The NPT_StringFinder class is used to determine if a string is found 
 as part of a list of strings.
 */
class NPT_StringFinder
{
public:
    // methods
    NPT_StringFinder(const char* value, bool ignore_case = false) : 
        m_Value(value), m_IgnoreCase(ignore_case) {}
    virtual ~NPT_StringFinder() {}
    bool operator()(const NPT_String* const & value) const {
        return value->Compare(m_Value, m_IgnoreCase) ? false : true;
    }
    bool operator()(const NPT_String& value) const {
        return value.Compare(m_Value, m_IgnoreCase) ? false : true;
    }

private:
    // members
    NPT_String   m_Value;
    bool         m_IgnoreCase;
};

/*----------------------------------------------------------------------
|   NPT_IpAddressFinder
+---------------------------------------------------------------------*/
/**
 The NPT_IpAddressFinder class is used to determine if a IP Address is found 
 as part of a list of IP Addresses.
 */
class NPT_IpAddressFinder
{
public:
    // methods
    NPT_IpAddressFinder(NPT_IpAddress ip) : 
        m_Value(ip) {}
    virtual ~NPT_IpAddressFinder() {}

    bool operator()(const NPT_IpAddress* const & value) const {
        return *value == m_Value;
    }
    bool operator()(const NPT_IpAddress& value) const {
        return value == m_Value;
    }

private:
    // members
    NPT_IpAddress m_Value;
};


/*----------------------------------------------------------------------
|   PLT_UPnPMessageHelper class
+---------------------------------------------------------------------*/
/**
 The PLT_UPnPMessageHelper class is a set of utility functions for manipulating 
 specific UPnP HTTP headers.
 */
class PLT_UPnPMessageHelper
{
public:
    // methods
    static const NPT_String* GetST(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("ST"); 
    }
    static NPT_Result SetST(NPT_HttpMessage& message, 
                            const char*      st) { 
        return message.GetHeaders().SetHeader("ST", st); 
    }
    static const NPT_String* GetNT(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("NT"); 
    }
    static NPT_Result SetNT(NPT_HttpMessage& message, 
                            const char*      nt) { 
        return message.GetHeaders().SetHeader("NT", nt); 
    }
    static const NPT_String* GetNTS(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("NTS"); 
    }
    static NPT_Result SetNTS(NPT_HttpMessage& message, 
                             const char*      nts) { 
        return message.GetHeaders().SetHeader("NTS", nts); 
    }
    static const NPT_String* GetMAN(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("MAN"); 
    }
    static NPT_Result SetMAN(NPT_HttpMessage& message, 
                             const char*      man) { 
        return message.GetHeaders().SetHeader("MAN", man); 
    }
    static const NPT_String* GetLocation(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("Location"); 
    }
    static NPT_Result SetLocation(NPT_HttpMessage& message, 
                                  const char*      location) { 
        return message.GetHeaders().SetHeader("Location", location); 
    }
    static const NPT_String* GetServer(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue(NPT_HTTP_HEADER_SERVER); 
    }
    static NPT_Result SetServer(NPT_HttpMessage& message, 
                                const char*      server, 
                                bool             replace = true) { 
        return message.GetHeaders().SetHeader(
            NPT_HTTP_HEADER_SERVER, 
            server, 
            replace); 
    }
    static const NPT_String* GetUSN(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("USN"); 
    }
    static NPT_Result SetUSN(NPT_HttpMessage& message, 
                             const char*      usn) { 
        return message.GetHeaders().SetHeader("USN", usn); 
    }
    static const NPT_String* GetCallbacks(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("CALLBACK"); 
    }
    static NPT_Result SetCallbacks(NPT_HttpMessage& message, 
                                   const char*      callbacks) { 
        return message.GetHeaders().SetHeader("CALLBACK", callbacks); 
    }
    static const NPT_String* GetSID(const NPT_HttpMessage& message) { 
        return message.GetHeaders().GetHeaderValue("SID"); 
    }
    static NPT_Result SetSID(NPT_HttpMessage& message, 
                             const char*      sid) { 
        return message.GetHeaders().SetHeader("SID", sid); 
    }
    static NPT_Result GetLeaseTime(const NPT_HttpMessage& message, 
                                   NPT_TimeInterval&      lease) { 
        const NPT_String* cc = 
            message.GetHeaders().GetHeaderValue("Cache-Control");
        NPT_CHECK_POINTER(cc);
        return ExtractLeaseTime(*cc, lease);
    }
    static NPT_Result SetLeaseTime(NPT_HttpMessage&        message, 
                                   const NPT_TimeInterval& lease) { 
        return message.GetHeaders().SetHeader(
            "Cache-Control", 
            "max-age="+NPT_String::FromInteger(lease.ToSeconds())); 
    }
    static NPT_Result GetTimeOut(const NPT_HttpMessage& message, 
                                 NPT_Int32&             seconds) { 
        seconds = 0;
        const NPT_String* timeout = 
            message.GetHeaders().GetHeaderValue("TIMEOUT"); 
        NPT_CHECK_POINTER(timeout);
        return ExtractTimeOut(*timeout, seconds); 
    }
    static NPT_Result SetTimeOut(NPT_HttpMessage& message, 
                                 const NPT_Int32  seconds) { 
        if (seconds >= 0) {
            return message.GetHeaders().SetHeader(
                "TIMEOUT", 
                "Second-"+NPT_String::FromInteger(seconds)); 
        } else {
            return message.GetHeaders().SetHeader(
                "TIMEOUT", 
                "Second-infinite"); 
        }
    }
    static NPT_Result GetIfModifiedSince(const NPT_HttpMessage& message,
                                         NPT_DateTime&          date) {
        
        const NPT_String* value = 
            message.GetHeaders().GetHeaderValue("If-Modified-Since");
        NPT_CHECK_POINTER(value);
        // Try RFC 1123, RFC 1036, then ANSI
        if (NPT_SUCCEEDED(date.FromString(*value, NPT_DateTime::FORMAT_RFC_1123))) 
            return NPT_SUCCESS;
        if (NPT_SUCCEEDED(date.FromString(*value, NPT_DateTime::FORMAT_RFC_1036)))
            return NPT_SUCCESS;
        return date.FromString(*value, NPT_DateTime::FORMAT_ANSI);
    }            
    static NPT_Result SetIfModifiedSince(NPT_HttpMessage&    message,
                                         const NPT_DateTime& date) {
        return message.GetHeaders().SetHeader(
            "If-Modified-Since",
            date.ToString(NPT_DateTime::FORMAT_RFC_1123));
    }
    static NPT_Result GetMX(const NPT_HttpMessage& message, 
                            NPT_UInt32&            value) { 
        value = 0;
        const NPT_String* mx = 
            message.GetHeaders().GetHeaderValue("MX");
        NPT_CHECK_POINTER(mx);
        return NPT_ParseInteger32(*mx, value, false); // no relax to be UPnP compliant
    }
    static NPT_Result SetMX(NPT_HttpMessage& message, 
                            const NPT_UInt32 mx) {
        return message.GetHeaders().SetHeader(
            "MX", 
            NPT_String::FromInteger(mx)); 
    }
    static NPT_Result GetSeq(const NPT_HttpMessage& message,  
                             NPT_UInt32&      value) { 
        value = 0;
        const NPT_String* seq = 
            message.GetHeaders().GetHeaderValue("SEQ");
        NPT_CHECK_POINTER(seq);
        return NPT_ParseInteger32(*seq, value);
    }
    static NPT_Result SetSeq(NPT_HttpMessage& message, 
                             const NPT_UInt32 seq) {
        return message.GetHeaders().SetHeader(
            "SEQ", 
            NPT_String::FromInteger(seq)); 
    }
    static const char* GenerateUUID(int         count, 
                                    NPT_String& uuid) {   
        uuid = "";
        for (int i=0;i<(count<100?count:100);i++) {
            int random = NPT_System::GetRandomInteger();
            uuid += (char)((random % 25) + 66);
        }
        return uuid;
    }
    static const char* GenerateGUID(NPT_String& guid) {   
        guid = "";
        for (int i=0;i<32;i++) {
            char nibble = (char)(NPT_System::GetRandomInteger() % 16);
            guid += (nibble < 10) ? ('0' + nibble) : ('a' + (nibble-10));
            if (i == 7 || i == 11 || i == 15 || i == 19) {
                guid += '-';
            }
        }
        return guid;
    }
    static NPT_Result ExtractLeaseTime(const NPT_String& cache_control, 
                                       NPT_TimeInterval& lease) {
        NPT_Int32 value;
        if (cache_control.StartsWith("max-age=", true) &&
            NPT_SUCCEEDED(NPT_ParseInteger32(cache_control.GetChars()+8, 
                                             value))) {
            lease.SetSeconds(value);
            return NPT_SUCCESS;
        }
        return NPT_FAILURE;
    }
    static NPT_Result ExtractTimeOut(const char* timeout, 
                                     NPT_Int32&  len) {
        NPT_String temp = timeout;
        if (temp.CompareN("Second-", 7, true)) {
            return NPT_ERROR_INVALID_FORMAT;
        }

        if (temp.Compare("Second-infinite", true) == 0) {
            len = NPT_TIMEOUT_INFINITE;
            return NPT_SUCCESS;
        }
        return temp.SubString(7).ToInteger(len);
    }
    static NPT_Result GetIPAddresses(NPT_List<NPT_IpAddress>& ips, 
                                     bool with_localhost = false) {
        NPT_List<NPT_NetworkInterface*> if_list;
        NPT_CHECK(GetNetworkInterfaces(if_list, with_localhost));

        NPT_List<NPT_NetworkInterface*>::Iterator iface = if_list.GetFirstItem();
        while (iface) {
            NPT_IpAddress ip = (*(*iface)->GetAddresses().GetFirstItem()).GetPrimaryAddress();
            if (ip.ToString().Compare("0.0.0.0") && 
                (with_localhost || ip.ToString().Compare("127.0.0.1"))) {
                ips.Add(ip);
            }
            ++iface;
        }

        if (with_localhost && !ips.Find(NPT_IpAddressFinder(NPT_IpAddress(127, 0, 0, 1)))) {
            NPT_IpAddress localhost;
            localhost.Parse("127.0.0.1");
            ips.Add(localhost);
        }

        if_list.Apply(NPT_ObjectDeleter<NPT_NetworkInterface>());
        return NPT_SUCCESS;
    }

    static NPT_Result GetNetworkInterfaces(NPT_List<NPT_NetworkInterface*>& if_list, 
                                           bool with_localhost = false) {
        NPT_CHECK(_GetNetworkInterfaces(if_list, false));

        // if no valid interfaces or if requested, add localhost interface
        if (if_list.GetItemCount() == 0 || with_localhost) {
            NPT_CHECK(_GetNetworkInterfaces(if_list, true));
        }
        return NPT_SUCCESS;
    }

	static NPT_Result GetMACAddresses(NPT_List<NPT_String>& addresses) {
        NPT_List<NPT_NetworkInterface*> if_list;
        NPT_CHECK(GetNetworkInterfaces(if_list));

        NPT_List<NPT_NetworkInterface*>::Iterator iface = if_list.GetFirstItem();
        while (iface) {
            NPT_String ip = (*(*iface)->GetAddresses().GetFirstItem()).GetPrimaryAddress().ToString();
            if (ip.Compare("0.0.0.0") && ip.Compare("127.0.0.1")) {
				addresses.Add((*iface)->GetMacAddress().ToString());
            }
            ++iface;
        }

        if_list.Apply(NPT_ObjectDeleter<NPT_NetworkInterface>());
        return NPT_SUCCESS;
    }


	static bool IsLocalNetworkAddress(const NPT_IpAddress& address) {
		if (address.ToString() == "127.0.0.1") return true;

		NPT_List<NPT_NetworkInterface*> if_list;
        NPT_NetworkInterface::GetNetworkInterfaces(if_list);

		NPT_List<NPT_NetworkInterface*>::Iterator iface = if_list.GetFirstItem();
        while (iface) {
			if((*iface)->IsAddressInNetwork(address)) return true;
            ++iface;
        }

		if_list.Apply(NPT_ObjectDeleter<NPT_NetworkInterface>());
		return false;
	}

private:

    static NPT_Result _GetNetworkInterfaces(NPT_List<NPT_NetworkInterface*>& if_list, 
                                            bool only_localhost = false) {
        NPT_List<NPT_NetworkInterface*> _if_list;
        NPT_CHECK(NPT_NetworkInterface::GetNetworkInterfaces(_if_list));

        NPT_NetworkInterface* iface;
        while (NPT_SUCCEEDED(_if_list.PopHead(iface))) {
            // only interested in non PTP & multicast capable interfaces
            if ((iface->GetAddresses().GetItemCount() == 0)||
                (!(iface->GetFlags() & NPT_NETWORK_INTERFACE_FLAG_MULTICAST)) ||
                (iface->GetFlags() & NPT_NETWORK_INTERFACE_FLAG_POINT_TO_POINT)) {
                delete iface;
                continue;
            }

            NPT_String ip = iface->GetAddresses().GetFirstItem()->GetPrimaryAddress().ToString();
            
            if (only_localhost && (iface->GetFlags() & NPT_NETWORK_INTERFACE_FLAG_LOOPBACK)) {
                if_list.Add(iface);
                break;
            } else  if (ip.Compare("0.0.0.0")) {
                if_list.Add(iface);
            } else {
                delete iface;
            }
        }

        // cleanup any remaining items in list if we breaked early
        _if_list.Apply(NPT_ObjectDeleter<NPT_NetworkInterface>());
        return NPT_SUCCESS;
    }
};

#endif /* _PLT_UPNP_HELPER_H_ */
