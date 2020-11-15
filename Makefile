# -----------------------------------------------------------------------------
# configurations.
# -----------------------------------------------------------------------------

C_FMT=docker run --rm -ti \
			--user `id -u ${USER}`:`id -g ${USER}` \
			-v `pwd`:/workdir xiejw/clang-format \
			/clang-format.sh

LIBS=2020-01_splittable_prng

# -----------------------------------------------------------------------------
# actions.
# -----------------------------------------------------------------------------
compile:
	@for lib in ${LIBS}; do \
		echo 'compile' $$lib && make --quiet -C $$lib > /dev/null; \
	done

fmt:
	@echo "fmt" && ${C_FMT} ${LIBS}

