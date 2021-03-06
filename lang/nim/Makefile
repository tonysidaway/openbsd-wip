# $OpenBSD: Makefile,v 1.3 2015/04/21 15:22:35 jturner Exp $

ONLY_FOR_ARCHS =	i386 amd64

COMMENT =		statically typed, imperative programming language

VERSION =		0.11.2
DISTNAME =		nim-${VERSION}
EXTRACT_SUFX =		.tar.xz

CATEGORIES =		lang

MAINTAINER =		James Turner <james@calminferno.net>

HOMEPAGE =		http://nim-lang.org/
MASTER_SITES =		http://nim-lang.org/download/

# MIT
PERMIT_PACKAGE_CDROM =	Yes

WANTLIB =		c m

NO_TEST =		Yes

do-build:
	cd ${WRKDIST} && ${SETENV} CC="${CC}" LINKER="${CC}" \
		COMP_FLAGS="${CFLAGS}" sh build.sh
	# slow machines can get a head of themselves and fail to link
	cd ${WRKSRC} && ${SETENV} bin/nim c --parallelBuild:1 koch
	cd ${WRKSRC} && ${SETENV} ./koch boot -d:release --parallelBuild:1

do-install:
	${INSTALL_PROGRAM_DIR} ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/bin/nim ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/lib/nim
	cp -R ${WRKSRC}/lib/* ${PREFIX}/lib/nim
	chown -R ${LIBOWN}:${LIBGRP} ${PREFIX}/lib/nim
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/nim
	${INSTALL_DATA} ${WRKSRC}/doc/*.txt ${PREFIX}/share/doc/nim
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/nim
	${INSTALL_DATA} ${WRKSRC}/config/*.cfg ${PREFIX}/share/examples/nim

.include <bsd.port.mk>
