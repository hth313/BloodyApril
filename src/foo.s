
              .section vram,data
              .public alboatros_II
              .align  256

alboatros_II: .incbin "assets/Albatros-trial.raw"


              .section palette1,data
              .public palette
palette:      .incbin "assets/Albatros-trial.raw.pal"
