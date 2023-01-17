imports["env"] = {
  malloc: (len) => {
    return wasm.__wbindgen_malloc(len);
  },
  calloc: (len) => {
    return wasm.__wbindgen_malloc(len);
  },
  free: (ptr) => {
    return wasm.__wbindgen_free(ptr);
  },
  realloc: (ptr, len) => {
    return wasm.__wbindgen_realloc(ptr, len);
  },
  fwrite: (ptr, size, count, stream) => {
    console.log(getStringFromWasm0(ptr, count));
  },
  fprintf: (stream, ptr) => {
    let len = 0;
    while (getUint8Memory0()[ptr + len] != 0) {
      len += 1;
    }
    const str = cachedTextDecoder.decode(
      getUint8Memory0().subarray(ptr, ptr + len),
    );
    console.log(str);
  },
  fputs: (ptr, stream) => {
    let len = 0;
    while (getUint8Memory0()[ptr + len] != 0) {
      len += 1;
    }
    const str = cachedTextDecoder.decode(
      getUint8Memory0().subarray(ptr, ptr + len),
    );
    console.log(str);
  },
  fflush: (stream) => {},
  abort: () => {
    throw new Error("abort");
  },
};
