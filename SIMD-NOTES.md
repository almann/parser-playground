# SIMD References

As I look into exploring SIMD/Compiler intrinsics, here are some handy references for learning:

JSON:
* [`simdjson` QCon Talk][simdjson-talk]
* [`simdjson` Parser][simdjson-gh]

UTF-8:
* [Fast Conversion From UTF-8 with C++, DFAs, and SSE Intrinsics][utf8-simd-talk]
* [UTF-8 Processing Using SIMD][utf8-simd]
* [Vectorized UTF-8 Conversion using `stdx::simd`][utf8-stdx-simd]
* [SIMD Text Processing with Parallel Bit Streams][simd-u8u16]

Base-64:
* [SSE Base64 Encoding][sse-base64] (discusses the use of `PSHUFB` for table lookups)
* [AVX-512 Base64 Encoding][avx512-base64] (Discusses the extending Base64 up to AVX-512)
* [`fastbase64` AVX2 base64 decoder][avx-base64]

Misc:
* [`PSHUFB`/`VPSHUFB` instructions][pshufb] (note that its AVX2 counterpart is not full 32-byte general) 
* [Data Parallel Finite State Machines][data-parallel-fsa]
* [Byte shuffle table lookup in WASM SIMD][wasm-simd-shuffle] (useful for examples in SSE/AVX/Neon)
* [Faster Lookup Tables using AVX2][faster-lookup-avx] (Stackoverflow question)
* [Iterating over set bits quickly using SIMD][iterating-over-set-bits]
* [Bits to indexes in BMI2 and AVX-512][bits-to-indexes-bmi-avx]
* [Pruning spaces faster on ARM processors with vector table lookups][pruning-space-arm]
* [Vectorized VByte Decoding][masked-vbyte] (code available [here][masked-vbyte-code])
* [SIMD Accelerated Regular Expression Processing][simd-regex]

* [C++ `std::experimental::simd`][cpp-std-simd]
* [Rust `packed_simd`][rust-packed-simd]

* [Intel Software Development Emulator][intel-sde] (Emulation/development support for various instruction sets, especially various AVX-512)

[simdjson-gh]: https://github.com/simdjson/simdjson
[simdjson-talk]: https://www.infoq.com/presentations/simdjson-parser/
[utf8-simd-talk]: https://www.youtube.com/watch?v=5FQ87-Ecb-A
[utf8-simd]: https://woboq.com/blog/utf-8-processing-using-simd.html
[utf8-stdx-simd]: https://mattkretz.github.io/2019/05/27/vectorized-conversion-from-utf8-using-stdx-simd.html
[simd-u8u16]: https://www2.cs.sfu.ca/~cameron/ppopp074-cameron.pdf
[avx-base64]: https://github.com/lemire/fastbase64
[sse-base64]: http://0x80.pl/notesen/2016-01-12-sse-base64-encoding.html
[avx512-base64]: http://0x80.pl/notesen/2016-04-03-avx512-base64.html
[pshufb]: https://www.felixcloutier.com/x86/pshufb
[data-parallel-fsa]: https://www.microsoft.com/en-us/research/publication/data-parallel-finite-state-machines/
[wasm-simd-shuffle]: https://github.com/WebAssembly/simd/issues/24
[faster-lookup-avx]: https://stackoverflow.com/questions/35789996/faster-lookup-tables-using-avx2#35790337
[iterating-over-set-bits]: https://lemire.me/blog/2018/03/08/iterating-over-set-bits-quickly-simd-edition/
[bits-to-indexes-bmi-avx]: https://branchfree.org/2018/05/22/bits-to-indexes-in-bmi2-and-avx-512/
[pruning-space-arm]: https://lemire.me/blog/2017/07/10/pruning-spaces-faster-on-arm-processors-with-vector-table-lookups/
[masked-vbyte]: https://arxiv.org/abs/1503.07387
[masked-vbyte-code]: http://maskedvbyte.org/
[simd-regex]: http://www.cs.columbia.edu/~orestis/damon16.pdf
[cpp-std-simd]: https://github.com/VcDevel/std-simd
[rust-packed-simd]: https://github.com/rust-lang/packed_simd
[intel-sde]: https://software.intel.com/content/www/us/en/develop/articles/intel-software-development-emulator.html