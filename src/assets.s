
sprite:	      .macro sym, sprite_file
              .section vram,data
              .align  256
              .public \sym
\sym:	      .incbin "\sprite_file"
	      .endm

	      sprite  SopwithPup_sprite, "assets/Pup.raw"
	      sprite  SopwithTriplane_sprite, "assets/Triplane.raw"
	      sprite  Albatros_D5a_J3_sprite, "assets/Albatros-D5a-J3.raw"
	      sprite  Albatros_D2_sprite, "assets/Alatros-D2.raw"
	      sprite  Albatros_D2_sprite_red_baron, "assets/Albatros-D2-Red-Baron.raw"

              .section palette1,data
              .public palette
palette:      .incbin "assets/BloodyAprilSprites.pal"
