
PACKAGE=glib

CURRDIR =${iPENGUIN_PATH_SPKG}/thrift/glib
WORKDIR =$(iPENGUIN_PATH_BUILD)/thrift
TARBALL =$(iPENGUIN_DISTFILES)/$(PACKAGE)
BUILDIR =$(WORKDIR)/$(PACKAGE)


ifneq ($(CC),x86_64-linux-gnu-gcc)

	CFLAGS += -I${iPENGUIN_ROOT_PATH}/build/thrift/${LIBICONV_PKG}/install_dst/include \
				-I${iPENGUIN_ROOT_PATH}/build/thrift/${GETTEXT_PKG}/install_dst/include \
				-I${iPENGUIN_ROOT_PATH}/build/thrift/${LIBFFI_PKG}/install_dst/lib/libffi-3.2.1/include
				

	LDFLAGS += -L${iPENGUIN_ROOT_PATH}/build/thrift/${LIBICONV_PKG}/install_dst/lib \
				-L${iPENGUIN_ROOT_PATH}/build/thrift/${GETTEXT_PKG}/install_dst/lib \
				-L${iPENGUIN_ROOT_PATH}/build/thrift/${LIBFFI_PKG}/install_dst/lib

	LIBS += -lffi -liconv

endif


ifeq ($(CC),mipsel-linux-gcc)
	CFLAGS += -I${iPENGUIN_ROOT_PATH}/build/sysutils/${ZLIB_PKG}/install_dst/include 
	LDFLAGS += -L${iPENGUIN_ROOT_PATH}/build/sysutils/${ZLIB_PKG}/install_dst/lib
	LIBS += -lz
endif

CONFIGS := CFLAGS="$(CFLAGS)"  LDFLAGS="$(LDFLAGS)" LIBS="$(LIBS)" \
			--with-pcre=internal --enable-libmount=no 

ifneq ($(CC),x86_64-linux-gnu-gcc)
   CONFIGS += --cache-file=android.cache --with-libiconv=gnu
endif



default: iPenguinPrepare $(iPENGUIN_DEPACKAGED) $(iPENGUIN_APPLYPATCH) $(iPENGUIN_CONFIGURED)
	$(MAKE) CC=$(CC) AR=$(AR) STRIP=$(STRIP) -C $(BUILDIR)
	$(MAKE) -C $(BUILDIR) install

$(iPENGUIN_DEPACKAGED):
	mkdir -p $(WORKDIR)
	cp $(TARBALL) $(WORKDIR) -a;
	touch $(iPENGUIN_DEPACKAGED)
	
$(iPENGUIN_APPLYPATCH): $(iPENGUIN_DEPACKAGED)
	$(Q)$(ECHO) "===== NEED NOT PATCH"
	touch $(iPENGUIN_APPLYPATCH)

$(iPENGUIN_CONFIGURED): $(iPENGUIN_DEPACKAGED)
	mkdir -p $(BUILDIR)/install_dst
	cd $(BUILDIR); autoreconf -i; ./configure CC=$(CC) AR=$(AR) --host=$(iPENGUIN_HOST) --prefix=$(BUILDIR)/install_dst $(CONFIGS)
	touch $(iPENGUIN_CONFIGURED)

clean:
	$(MAKE) -C $(BUILDIR) clean

distclean:
	$(RM) $(BUILDIR)
	$(RM) $(iPENGUIN_CONFIGURED) $(iPENGUIN_DEPACKAGED) $(iPENGUIN_APPLYPATCH)

test:
	echo $(iPENGUIN_DEV_INSTALL)

prepare:
	iPatchApply.sh CONF

patch: clean
	$(shell if [ ! -d ori ]; then mkdir ori;tar xzf $(TARBALL) -C ori; fi)
	iPatchGen.pl CONF

install: 
	cp $(BUILDIR)/install_dst/lib/libglib-2.0.so* $(iPENGUIN_INSTALL_PATH_LIB) -a
	cp $(BUILDIR)/install_dst/lib/libgobject-2.0.so* $(iPENGUIN_INSTALL_PATH_LIB) -a

#export iPENGUIN_INSTALL_PATH_DEVEL_HEAD=${iPENGUIN_PATH_EPKG}/include
#export iPENGUIN_INSTALL_PATH_DEVEL_LIB=${iPENGUIN_PATH_EPKG}/lib
#export iPENGUIN_INSTALL_PATH_BIN=${iPENGUIN_PATH_EPKG}/usr/bin
#export iPENGUIN_INSTALL_PATH_LIB=${iPENGUIN_PATH_EPKG}/usr/lib
	
	

iPenguinPrepare :
	mkdir -p $(WORKDIR)
