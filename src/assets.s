
              .section vram,data
              .public SopwithPup_sprite

              .align  256
              .public albatros_D2_sprite
albatros_D2_sprite:
	      .incbin "assets/Albatros-trial.raw"

	      .public albatros_D5a_sprite
albatros_D5a_sprite:

SopwithPup_sprite:

              .section palette1,data
              .public palette
palette:      .incbin "assets/Albatros-trial.raw.pal"
