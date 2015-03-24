/*
 * networkcommon_conf.h: network XML handling
 *
 * Copyright (C) 2006-2014 Red Hat, Inc.
 * Copyright (C) 2006-2008 Daniel P. Berrange
 * Copyright (c) 2015 SUSE LINUX Products GmbH, Nuernberg, Germany.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Author: Daniel P. Berrange <berrange@redhat.com>
 */

#ifndef __NETWORKCOMMON_CONF_H__
# define __NETWORKCOMMON_CONF_H__

# include <libxml/tree.h>
# include <libxml/xpath.h>

# include "internal.h"
# include "virbuffer.h"
# include "virsocketaddr.h"

typedef struct _virNetworkRouteDef virNetworkRouteDef;
typedef virNetworkRouteDef *virNetworkRouteDefPtr;

struct _virNetworkRouteDef {
    char *family;               /* ipv4 or ipv6 - default is ipv4 */
    virSocketAddr address;      /* Routed Network IP address */

    /* One or the other of the following two will be used for a given
     * Network address, but never both. The parser guarantees this.
     * The virSocketAddrGetIpPrefix() can be used to get a
     * valid prefix.
     */
    virSocketAddr netmask;      /* ipv4 - either netmask or prefix specified */
    unsigned int prefix;        /* ipv6 - only prefix allowed */
    bool has_prefix;            /* prefix= was specified */
    unsigned int metric;        /* value for metric (defaults to 1) */
    bool has_metric;            /* metric= was specified */
    virSocketAddr gateway;      /* gateway IP address for ip-route */
};

void
virNetworkRouteDefFree(virNetworkRouteDefPtr def);

virNetworkRouteDefPtr
virNetworkRouteDefCreate(const char *networkName,
                         char *family,
                         const char *address,
                         const char *netmask,
                         const char *gateway,
                         unsigned int prefix,
                         bool hasPrefix,
                         unsigned int metric,
                         bool hasMetric);

virNetworkRouteDefPtr
virNetworkRouteDefParseXML(const char *networkName,
                           xmlNodePtr node,
                           xmlXPathContextPtr ctxt);
int
virNetworkRouteDefFormat(virBufferPtr buf,
                         const virNetworkRouteDef *def);

virSocketAddrPtr
virNetworkRouteDefGetAddress(virNetworkRouteDefPtr def);

int
virNetworkRouteDefGetPrefix(virNetworkRouteDefPtr def);

unsigned int
virNetworkRouteDefGetMetric(virNetworkRouteDefPtr def);

virSocketAddrPtr
virNetworkRouteDefGetGateway(virNetworkRouteDefPtr def);

#endif /* __NETWORKCOMMON_CONF_H__ */
