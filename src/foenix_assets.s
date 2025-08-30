#ifdef __CALYPSI_TARGET_M68K__
#define VRAM_OFFSET 0x00c00000
sprite:	      .macro  sym, sprite_file
              .align  2
              .public \sym
\sym:         .byte   .byte0 (sprite_data$ - VRAM_OFFSET)
              .byte   2 + 1          ; control byte, LUT1 & enable
              .word   .word1 (sprite_data$ - VRAM_OFFSET)
              .word   0,0
              .section vram,data
              .align  256
sprite_data$: .incbin "\sprite_file"
              .section near,data
              .endm
#else
#define VRAM_OFFSET 0xb00000
sprite:       .macro sym, sprite_file
              .public \sym
\sym:         .byte   2 + 1          ; control byte, LUT1 & enable
              .word   .word0 (sprite_data$ - VRAM_OFFSET)
              .byte   .byte2 (sprite_data$ - VRAM_OFFSET)
              .word   0,0
              .section vram,data
              .align  256
sprite_data$: .incbin "\sprite_file"
              .section near,data
              .endm
#endif
              sprite  SopwithPup_sprite, "../assets/sprites-17.sprite"
              sprite  SopwithTriplane_sprite, "../assets/sprites-19.sprite"
              sprite  Albatros_D5a_J3_sprite, "../assets/sprites-16.sprite"
              sprite  Albatros_D2_sprite, "../assets/sprites-18.sprite"


              sprite  Albatros_D2_sprite_red_baron, "../assets/sprites-20.sprite"

              sprite  right_facing_dogfight_sprite, "../assets/sprites-24.sprite"
              sprite  left_facing_dogfight_sprite, "../assets/sprites-25.sprite"

              sprite  allied_aerodrome_sprite, "../assets/sprites-26.sprite"
              sprite  central_aerodrome_sprite, "../assets/sprites-27.sprite"

              .section palette1,data
              .public palette
palette:      .incbin "../assets/trench1.palette"

// ----------------------------------------------------------------------
// Tile maps

tiles:        .macro  tiles
              .section vram,data
              .public \tiles_index, \tiles_tiles
#ifdef __BIG_ENDIAN__
\tiles_index: .incbin "../assets/\tiles-big-endian.index"
#else
\tiles_index: .incbin "../assets/\tiles-little-endian.index"
#endif
\tiles_tiles: .incbin "../assets/\tiles.tiledata"
              .endm

              tiles   trench1
              tiles   towns
