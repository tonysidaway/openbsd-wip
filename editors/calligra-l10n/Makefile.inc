# $OpenBSD: Makefile.inc,v 1.8 2015/04/12 18:06:32 zhuk Exp $

IGNORE_SILENT =		Yes
CATEGORIES =		editors editors/calligra-l10n
COMMENT =		Calligra localization pack
VERSION =		2.9.7
DISTNAME =		calligra-l10n-${L10N_LANG}-${VERSION}

PERMIT_PACKAGE_CDROM =	Yes

MODKDE4_RESOURCES =	Yes
MODKDE4_USE =		libs

.include "${.CURDIR}/../Makefile.langs"

.for L in ${ALL_LANGS}
SUPDISTFILES +=	calligra-l10n-${L}-${VERSION}${EXTRACT_SUFX}
.endfor

RUN_DEPENDS +=	x11/gtk+3,-guic

MASTER_SITES =	${MASTER_SITE_KDE:=stable/calligra-${VERSION}/calligra-l10n/}

LANG_STR =	${L10N_LANG} language
SUBST_VARS =	LANG_STR

PKGDIR =	${.CURDIR}/../pkg
DESCR =		${PKGDIR}/DESCR
PLIST =		${PKGDIR}/PLIST-${L10N_LANG}
CHECKSUM_FILE =	${.CURDIR}/../distinfo

MODULES +=	x11/kde4 devel/gettext
NO_TEST =	Yes
CONFIGURE_ENV =	CFLAGS=-I${PREFIX}/include \
		LDFLAGS="-L${PREFIX}/lib -liconv -lintl"

MODKDE4_FIX_GETTEXT =	Yes

CONFIGURE_ARGS +=	-DCMAKE_POLICY_DEFAULT_CMP0014=OLD

WANTLIB- =

post-install:
	rm -Rf ${PREFIX}/man/${L10N_LANG}/
