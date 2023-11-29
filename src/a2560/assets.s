#define VRAM_OFFSET 0x00c00000

sprite:       .macro sym, sprite_file
              .align  2
              .public \sym
\sym:         .byte   .byte0 (sprite_data$ - VRAM_OFFSET)
              .byte   1             ; control byte
              .word   .word1 (sprite_data$ - VRAM_OFFSET)
              .word   0,0
              .section vram,data
              .align  256
sprite_data$: .incbin "\sprite_file"
              .section near,data
              .endm

              sprite  SopwithPup_sprite, "assets/Pup.raw"
              sprite  SopwithTriplane_sprite, "assets/Triplane.raw"
              sprite  Albatros_D5a_J3_sprite, "assets/Albatros-D5a-J3.raw"
              sprite  Albatros_D2_sprite, "assets/Alatros-D2.raw"


              sprite  Albatros_D2_sprite_red_baron, "assets/Albatros-D2-Red-Baron.raw"

	      sprite  right_facing_dogfight_sprite, "../assets/sprites-24.sprite"
	      sprite  left_facing_dogfight_sprite, "../assets/sprites-25.sprite"

	      sprite  allied_aerodrome_sprite_data, "../assets/sprites-26.sprite"
	      sprite  central_aerodrome_sprite_data, "../assets/sprites-27.sprite"

              .section palette1,data
              .public palette
palette:      .incbin "assets/BloodyAprilSprites.pal"

// ----------------------------------------------------------------------
// Tile maps

tiles:        .macro  tiles
              .section vram,data
              .public \tiles_index, \tiles_tiles
\tiles_index: .incbin "../assets/\tiles.index"
\tiles_tiles: .incbin "../assets/\tiles.tiledata"
	      .endm

              tiles   trench1
              tiles   towns
