# $OpenBSD$

ONLY_FOR_ARCHS =	${GO_ARCHS}

COMMENT =		Go programming language

EXTRACT_SUFX =		.tar.gz
DISTNAME = 		go-${VERSION}${PL}
CATEGORIES =		lang

HOMEPAGE =		http://golang.org/

MAINTAINER = 		Joel Sing <jsing@openbsd.org>

# software: BSD, documentation: CC-BY-3.0
PERMIT_PACKAGE_CDROM =	Yes

WANTLIB =		c m pthread

MASTER_SITES0 ?=	http://golang.org/dl/
MASTER_SITES1 =		https://github.com/golang/tools/archive/

DISTFILES =		${DISTNAME}{go${VERSION}${PL}.src}${EXTRACT_SUFX}:0 \
			go-tools-${GT_DATE}{${GT_COMMIT}}${EXTRACT_SUFX}:1

SEPARATE_BUILD =	simple
CONFIGURE_STYLE =	None
SUBST_VARS =		GOEXE GOCFG VERSION

MODULES =		lang/python

BUILD_DEPENDS +=	shells/bash

WRKDIST =		${WRKDIR}/go
WRKSRC =		${WRKDIST}/src

GOOS = 			openbsd
GOARCH =		unknown
GOROOT = 		${PREFIX}/go/${VERSION}

.if ${MACHINE_ARCH} == "amd64"
GOARCH =		amd64
EXEPREFIX =		6
PKG_ARGS +=		-Damd64=1
PKG_ARGS +=		-Di386=0
.elif ${MACHINE_ARCH} == "i386"
GOARCH =		386
EXEPREFIX =		8
PKG_ARGS +=		-Damd64=0
PKG_ARGS +=		-Di386=1
.else
PKG_ARGS += 		-Damd64=0 -Di386=0
.endif

GOCFG =			/${GOOS}_${GOARCH}
GOEXE =			${GOCFG}/${EXEPREFIX}

MAKE_ENV =		CC="${CC}" \
			CXX="${CXX}" \
			GOROOT=${WRKDIST} \
			GOBIN=${WRKDIST}/bin \
			GOROOT_FINAL=${GOROOT}

# Go 1.5+ needs this, and 1.4 ignores this
MAKE_ENV +=		GOROOT_BOOTSTRAP=${GOROOT:H}/1.4

# Go tools need this
MAKE_ENV +=		GOPATH="${WRKDIR}/tools/go"

do-configure:
.	if ${GOARCH} == "unknown"
		@echo "Unable to determine GOARCH for ${MACHINE_ARCH}."
		@exit 1
.	endif
	mkdir -p ${WRKDIR}/tools/go/src/golang.org/x
	mv ${WRKDIR}/tools-${GT_COMMIT} ${WRKDIR}/tools/go/src/golang.org/x/tools

do-build:
	@cd ${WRKSRC} && ${MAKE_ENV} ./make.bash --no-banner
.for tool in ${TOOLS}
	${MAKE_ENV} ${WRKDIST}/bin/go install golang.org/x/tools/cmd/${tool}
.endfor

do-test:
	@cd ${WRKSRC} && \
		ulimit -n 256 -d 2097152 && \
		PATH=${WRKDIST}/bin:${PATH} GOROOT=${WRKDIST} ./run.bash

do-install:
	${INSTALL_PROGRAM_DIR} ${GOROOT}/bin

	${INSTALL_PROGRAM} -p ${WRKDIST}/bin/* ${GOROOT}/bin

	@cd ${WRKDIST} && \
		find . ! -name .hg\* -type f -maxdepth 1 \
			-exec ${INSTALL_DATA} -p {} \
			${GOROOT} \;

.	for dir in ${DIRS}
		@cd ${WRKDIST} && \
			find ${dir} -type d \
				-exec ${INSTALL_DATA_DIR} \
				${GOROOT}/{} \;
		@cd ${WRKDIST} && \
			find ${dir} ! -name \*.orig -type f \
				-exec ${INSTALL_DATA} -p {} \
				${GOROOT}/{} \;
.	endfor

	# These get installed via `find' however we need them to be executable
	${INSTALL_PROGRAM_DIR} ${GOROOT}/pkg/tool/${GOOS}_${GOARCH}
	${INSTALL_PROGRAM} -p ${WRKDIST}/pkg/tool/${GOOS}_${GOARCH}/* \
		${GOROOT}/pkg/tool/${GOOS}_${GOARCH}

	# Compile python scripts
	@find ${PREFIX} -name \*.py \
		-exec ${MODPY_BIN} ${MODPY_LIBDIR}/compileall.py {} +
