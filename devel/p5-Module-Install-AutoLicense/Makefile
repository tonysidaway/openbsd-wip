# $OpenBSD: Makefile.template,v 1.71 2014/07/10 12:33:17 sthen Exp $

COMMENT =		module install extention AutoLicense

DISTNAME =		Module-Install-AutoLicense-0.08
CATEGORIES =		devel

# Perl
PERMIT_PACKAGE_CDROM =	Yes

MODULES =		cpan

RUN_DEPENDS =		devel/p5-Software-License
BUILD_DEPENDS +=	${RUN_DEPENDS} \
			devel/p5-Module-Install \
			sysutils/p5-Capture-Tiny>=0.05

MAKE_ENV +=		TEST_POD=Yes

TEST_DEPENDS +=		devel/p5-Test-Pod-Coverage

.include <bsd.port.mk>
