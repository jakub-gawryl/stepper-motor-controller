void exampleA() {
  /**
   * Example of writing 1 byte value 0xFF (or 0b1111 1111)
   * to register with memory address of 0x25 (or 0b0010 0101)
   * 
   * example: *((volatile unsigned char*) 0x25) = 0xFF;
   * 
   * steps:
   * - 1. cast "0x25" hex number to volatile byte pointer ("unsigned char*" is basically "byte*")
   *    (volatile unsigned char*) 0x25
   * 
   * - 2. dereference it by using first asterisk sign...
   *    *( ... )
   * 
   * - 3. ... which then will set the value of that address to 0xFF
   *    ... = 0xFF
   */

  // *((volatile unsigned char*) 0x25) = 0xFF;
}