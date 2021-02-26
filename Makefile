apps = $(sort $(dir $(wildcard apps/*/)))

all:
	@for app in $(apps) ; do \
		make -C $$app all; \
	done

clean:
	@for app in $(apps) ; do \
		make -C $$app clean; \
	done
	@rm -rf dist/*