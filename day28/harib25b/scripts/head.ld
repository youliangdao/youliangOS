/* UNIXのELF実行ファイル形式にしないでバイナリで出力させる */
OUTPUT_FORMAT("binary")

SECTIONS
{
        . = 0xc200;
        /* .textのセクションは、ROMのメモリー領域へ */
        .text : { *(.text) }
}