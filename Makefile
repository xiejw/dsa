# -----------------------------------------------------------------------------
# configurations.
# -----------------------------------------------------------------------------

C_FMT=docker run --rm -ti \
			--user `id -u ${USER}`:`id -g ${USER}` \
			-v `pwd`:/workdir xiejw/clang-format \
			/clang-format.sh

LIBS=2020-01_splittable_prng 2020-10_skiplist 2020-11_dancing_links 2021_bloom_filter

# -----------------------------------------------------------------------------
# actions.
# -----------------------------------------------------------------------------
compile:
	@for lib in ${LIBS}; do \
		echo 'compile' $$lib && make --quiet -C $$lib > /dev/null; \
	done

fmt:
	@for lib in ${LIBS}; do \
		echo 'fmt' $$lib && ${C_FMT} $$lib; \
	done

