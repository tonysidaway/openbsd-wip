# $OpenBSD: Makefile,v 1.10 2015/04/02 14:21:18 jasper Exp $

COMMENT =		scalable, non-blocking web server

MODPY_EGG_VERSION =	4.2.1
DISTNAME =		tornado-${MODPY_EGG_VERSION}
PKGNAME =		py-${DISTNAME}

CATEGORIES =		www

HOMEPAGE =		http://www.tornadoweb.org/

# Apache v2
PERMIT_PACKAGE_CDROM =	Yes

MODPY_PI =		Yes

MODULES =		lang/python
RUN_DEPENDS +=		devel/py-backports-ssl-match-hostname
WANTLIB +=		pthread ${MODPY_WANTLIB}

MODPY_SETUPTOOLS =	Yes

pre-configure:
	${SUBST_CMD} ${WRKSRC}/runtests.sh

TEST_DEPENDS +=		${RUN_DEPENDS} \
			devel/py-twisted/names \
			devel/py-twisted/web \
			devel/py-mock \
			net/py-curl \
			devel/py-futures
# XXX one failing test
# test_openFileDescriptors
# FailTest: not equal:
# a = '[0, 1, 2, 3]'
# b = '[0, 1, 2]'
do-test:
	@cd ${WRKSRC} && sh runtests.sh

.include <bsd.port.mk>
