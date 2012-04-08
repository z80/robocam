
SUBDIRS		= 	client \
				server
				
				
all:
	@for subdir in $(SUBDIRS); \
	do \
		echo "making $@ in $$subdir"; \
		( cd $$subdir && $(MAKE) $@ ) || exit 1; \
	done

		
