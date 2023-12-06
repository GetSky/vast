// This is a modified version of the code developed by Patrick Glaschke
// and described in https://arxiv.org/abs/1008.3966

// ******************************************************** //
//    Fast determination of the constellation from          //
//    a given sky coordinate (equinox B1875.0).             //
//    Author: Patrick Glaschke (2010)                       //
//                                                          //
// Serpens Caput and Serpens Cauda are NOT reported separately. //
//                                                          //
// Constellation boundaries based on Catalogue VI/49 at     //
// http://vizier.cfa.harvard.edu/viz-bin/Cat?VI/49#sRM2.1   //
// ******************************************************** //

#include <stdio.h>
#include <stdlib.h> // for atof()

typedef struct zz {
 char cab[4];
} ZZ;
typedef struct node {
 int iSplit;
 double Split;
 int nLow;
 int nHi;
} NODE;

int Levels;

ZZ Names[89]= {
    { "And" }, { "Ant" }, { "Aps" }, { "Aqr" }, { "Aql" }, { "Ara" }, { "Ari" }, { "Aur" }, { "Boo" }, { "Cae" }, { "Cam" }, { "Cnc" }, { "CVn" }, { "CMa" }, { "CMi" }, { "Cap" }, { "Car" }, { "Cas" }, { "Cen" }, { "Cep" }, { "Cet" }, { "Cha" }, { "Cir" }, { "Col" }, { "Com" }, { "CrA" }, { "CrB" }, { "Crv" }, { "Crt" }, { "Cru" }, { "Cyg" }, { "Del" }, { "Dor" }, { "Dra" }, { "Equ" }, { "Eri" }, { "For" }, { "Gem" }, { "Gru" }, { "Her" }, { "Hor" }, { "Hya" }, { "Hyi" }, { "Ind" }, { "Lac" }, { "Leo" }, { "LMi" }, { "Lep" }, { "Lib" }, { "Lup" }, { "Lyn" }, { "Lyr" }, { "Men" }, { "Mic" }, { "Mon" }, { "Mus" }, { "Nor" }, { "Oct" }, { "Oph" }, { "Ori" }, { "Pav" }, { "Peg" }, { "Per" }, { "Phe" }, { "Pic" }, { "Psc" }, { "PsA" }, { "Pup" }, { "Pyx" }, { "Ret" }, { "Sge" }, { "Sgr" }, { "Sco" }, { "Scl" }, { "Sct" }, { "Ser" }, { "Ser" }, { "Sex" }, { "Tau" }, { "Tel" }, { "Tri" }, { "TrA" }, { "Tuc" }, { "UMa" }, { "UMi" }, { "Vel" }, { "Vir" }, { "Vol" }, { "Vul" } };

NODE Tree[714]= {
    { 0, 12.0000, 1, 363 }, { 1, 5.5000, 2, 184 }, { 1, -43.0000, 3, 99 }, { 0, 4.5000, 4, 52 }, { 0, 3.2000, 5, 30 }, { 1, -53.5000, 6, 19 }, { 0, 1.3333, 7, 12 }, { 1, -76.0000, 8, 9 }, { 1, -82.5000, -58, -43 }, { 1, -75.0000, 10, 11 }, { 0, 0.7500, -43, -83 }, { 1, -58.5000, -83, -64 }, { 1, -58.5000, 13, 16 }, { 1, -67.5000, 14, 15 }, { 1, -82.5000, -58, -43 }, { 0, 2.1667, -43, -41 }, { 1, -54.0000, 17, 18 }, { 0, 2.1667, -36, -41 }, { 0, 2.4167, -36, -41 }, { 0, 2.4167, 20, 25 }, { 0, 1.8333, 21, 23 }, { 0, 1.5833, -64, 22 }, { 1, -51.5000, -36, -64 }, { 0, 2.3333, 24, -36 }, { 1, -48.1667, -36, -64 }, { 1, -49.0000, 26, 28 }, { 0, 2.6667, 27, -41 }, { 1, -51.0000, -41, -36 }, { 0, 3.0000, -36, 29 }, { 1, -46.0000, -41, -36 }, { 1, -53.1667, 31, 43 }, { 1, -59.0000, 32, 38 }, { 0, 3.5000, 33, 35 }, { 1, -82.5000, -58, 34 }, { 1, -67.5000, -43, -70 }, { 1, -75.0000, 36, 37 }, { 1, -85.0000, -58, -53 }, { 1, -67.5000, -43, -70 }, { 0, 4.0000, 39, 41 }, { 0, 3.5000, 40, -70 }, { 1, -57.5000, -70, -41 }, { 0, 4.3333, 42, -33 }, { 1, -56.5000, -70, -33 }, { 1, -49.0000, 44, 47 }, { 1, -51.0000, 45, 46 }, { 0, 3.8333, -41, -33 }, { 0, 4.0833, -41, -33 }, { 0, 3.4167, 48, 49 }, { 1, -46.0000, -41, -36 }, { 0, 3.8667, 50, 51 }, { 1, -44.0000, -41, -36 }, { 0, 4.2667, -41, -10 }, { 1, -58.0000, 53, 75 }, { 0, 6.5833, 54, 65 }, { 0, 4.5833, 55, 59 }, { 1, -75.0000, 56, 57 }, { 1, -85.0000, -58, -53 }, { 1, -67.5000, -43, 58 }, { 1, -59.0000, -70, -33 }, { 1, -64.0000, 60, 62 }, { 1, -85.0000, -58, 61 }, { 1, -70.0000, -53, -33 }, { 1, -61.0000, 63, 64 }, { 0, 6.0000, -33, -65 }, { 0, 5.5000, -33, -65 }, { 1, -75.0000, 66, 69 }, { 0, 7.6667, 67, 68 }, { 1, -85.0000, -58, -53 }, { 1, -82.5000, -58, -22 }, { 1, -64.0000, 70, 72 }, { 0, 9.0333, -88, 71 }, { 0, 11.2500, -17, -56 }, { 0, 11.2500, 73, 74 }, { 0, 6.8333, -65, -17 }, { 0, 11.8333, -19, -30 }, { 0, 8.0000, 76, 88 }, { 0, 6.0000, 77, 83 }, { 0, 5.0000, 78, 81 }, { 1, -46.5000, 79, 80 }, { 1, -54.0000, -33, -65 }, { 0, 4.8333, -10, -65 }, { 0, 5.5000, 82, -65 }, { 1, -57.5000, -33, -65 }, { 1, -55.0000, 84, 85 }, { 0, 6.5000, -65, -17 }, { 1, -52.5000, 86, 87 }, { 0, 6.1667, -65, -17 }, { 1, -50.7500, -17, -68 }, { 0, 8.8333, 89, 94 }, { 1, -53.0000, 90, 92 }, { 0, 8.4500, -17, 91 }, { 1, -54.5000, -17, -86 }, { 0, 8.1667, 93, -86 }, { 1, -50.7500, -17, -86 }, { 0, 11.2500, 95, 97 }, { 1, -56.5000, -17, 96 }, { 0, 11.0000, -86, -19 }, { 0, 11.8333, -19, 98 }, { 1, -55.0000, -30, -19 }, { 0, 6.1167, 100, 138 }, { 1, -24.3833, 101, 120 }, { 0, 3.8667, 102, 111 }, { 0, 3.0000, 103, 107 }, { 1, -40.0000, 104, 105 }, { 0, 2.3333, -64, -36 }, { 0, 1.6667, 106, -37 }, { 1, -25.5000, -74, -21 }, { 0, 3.5000, 108, 109 }, { 1, -39.5833, -36, -37 }, { 0, 3.7500, 110, -36 }, { 1, -36.0000, -36, -37 }, { 0, 4.7000, 112, 117 }, { 1, -37.0000, 113, 115 }, { 0, 4.2667, 114, -10 }, { 1, -40.0000, -41, -36 }, { 0, 4.5833, -36, 116 }, { 1, -30.0000, -10, -36 }, { 1, -27.2500, 118, 119 }, { 0, 5.0000, -10, -24 }, { 0, 4.8333, -36, -48 }, { 0, 4.6667, 121, 131 }, { 0, 2.6500, 122, 126 }, { 0, 0.3333, 123, 124 }, { 1, -7.0000, -21, -66 }, { 0, 2.0000, 125, -21 }, { 1, 2.0000, -21, -66 }, { 0, 3.5833, 127, 129 }, { 1, -1.7500, -36, 128 }, { 0, 3.2833, -21, -79 }, { 1, 0.0000, -36, 130 }, { 0, 4.6167, -79, -60 }, { 1, -11.0000, 132, 135 }, { 1, -14.5000, 133, 134 }, { 0, 4.8333, -36, -48 }, { 0, 4.9167, -36, -48 }, { 1, -4.0000, 136, -60 }, { 0, 5.0833, -36, 137 }, { 0, 5.8333, -60, -55 }, { 0, 9.5833, 139, 161 }, { 0, 8.0833, 140, 150 }, { 1, -4.0000, 141, 145 }, { 1, -33.0000, 142, 143 }, { 0, 6.5833, -24, -68 }, { 1, -11.0000, 144, -55 }, { 0, 7.3667, -14, -68 }, { 0, 7.0167, 146, 147 }, { 0, 6.2417, -60, -55 }, { 0, 7.2000, 148, 149 }, { 1, 1.5000, -55, -15 }, { 1, 0.0000, -55, -15 }, { 1, -24.0000, 151, 155 }, { 0, 9.3667, 152, 154 }, { 0, 8.3667, -68, 153 }, { 1, -36.7500, -86, -69 }, { 1, -39.7500, -86, -2 }, { 0, 8.5833, 156, 159 }, { 0, 8.3667, 157, 158 }, { 1, -11.0000, -68, -42 }, { 1, -17.0000, -69, -42 }, { 0, 9.0833, 160, -42 }, { 1, -19.0000, -69, -42 }, { 1, -24.5000, 162, 172 }, { 1, -31.1667, 163, 167 }, { 1, -35.0000, 164, 166 }, { 0, 11.0000, 165, -19 }, { 1, -39.7500, -86, -2 }, { 0, 10.8333, -2, -42 }, { 0, 10.2500, 168, 170 }, { 0, 9.7500, -2, 169 }, { 1, -26.5000, -2, -42 }, { 0, 10.5833, 171, -42 }, { 1, -29.1667, -2, -42 }, { 1, -11.0000, 173, 179 }, { 0, 10.7500, 174, 176 }, { 0, 9.7500, 175, -42 }, { 1, -24.0000, -2, -42 }, { 0, 10.8333, 177, 178 }, { 1, -19.0000, -42, -29 }, { 0, 11.8333, -29, -28 }, { 1, -6.0000, 180, 182 }, { 0, 10.7500, -78, 181 }, { 0, 11.8333, -29, -87 }, { 0, 10.7500, -78, 183 }, { 0, 11.5167, -46, -87 }, { 1, 33.5000, 185, 272 }, { 0, 5.8833, 186, 230 }, { 0, 2.7167, 187, 208 }, { 0, 1.4083, 188, 198 }, { 0, 0.1417, 189, 193 }, { 1, 22.0000, 190, 191 }, { 1, 12.5000, -66, -62 }, { 0, 0.0667, 192, -1 }, { 1, 28.0000, -62, -1 }, { 1, 23.7500, 194, 196 }, { 0, 0.8500, 195, -66 }, { 1, 21.0000, -66, -1 }, { 0, 0.7167, -1, 197 }, { 1, 33.0000, -66, -1 }, { 0, 1.9167, 199, 203 }, { 0, 1.6667, 200, 201 }, { 1, 28.0000, -66, -81 }, { 1, 9.9167, -66, 202 }, { 1, 25.0000, -7, -81 }, { 1, 27.2500, 204, 206 }, { 1, 9.9167, 205, -7 }, { 0, 2.0000, -66, -21 }, { 0, 2.4167, -81, 207 }, { 1, 30.6667, -7, -81 }, { 1, 18.0000, 209, 220 }, { 0, 4.9667, 210, 214 }, { 0, 3.2833, 211, 212 }, { 1, 9.9167, -21, -7 }, { 0, 4.6167, -79, 213 }, { 1, 15.5000, -60, -79 }, { 0, 5.6000, 215, 218 }, { 0, 5.3333, 216, 217 }, { 1, 16.0000, -60, -79 }, { 1, 15.5000, -60, -79 }, { 0, 5.7667, 219, -60 }, { 1, 12.5000, -60, -79 }, { 0, 4.5000, 221, 225 }, { 1, 19.0000, 222, 223 }, { 0, 3.2833, -7, -79 }, { 1, 30.6667, 224, -63 }, { 0, 3.3667, -7, -79 }, { 1, 28.5000, 226, 228 }, { 0, 5.7000, -79, 227 }, { 1, 22.8333, -60, -79 }, { 0, 4.7500, 229, -8 }, { 1, 30.0000, -79, -8 }, { 0, 7.9250, 231, 251 }, { 0, 6.9333, 232, 241 }, { 1, 17.5000, 233, 237 }, { 0, 6.3083, 234, 236 }, { 0, 6.2417, -60, 235 }, { 1, 10.0000, -55, -60 }, { 1, 12.0000, -55, -38 }, { 1, 21.5000, 238, 239 }, { 0, 6.2167, -60, -38 }, { 0, 6.5333, 240, -38 }, { 1, 28.0000, -38, -8 }, { 0, 7.8083, 242, 247 }, { 1, 12.5000, 243, 245 }, { 0, 7.0000, 244, -15 }, { 1, 10.0000, -55, -38 }, { 0, 7.5000, -38, 246 }, { 1, 13.5000, -15, -38 }, { 1, 20.0000, 248, 249 }, { 1, 10.0000, -15, -12 }, { 0, 7.8833, -38, 250 }, { 1, 28.0000, -12, -38 }, { 0, 10.7500, 252, 263 }, { 0, 9.5833, 253, 258 }, { 1, 7.0000, 254, 255 }, { 0, 8.0833, -15, -42 }, { 0, 8.0000, 256, 257 }, { 1, 28.0000, -12, -38 }, { 0, 9.2500, -12, -46 }, { 1, 23.5000, 259, 260 }, { 1, 7.0000, -78, -46 }, { 1, 28.5000, 261, 262 }, { 0, 10.5000, -46, -47 }, { 0, 9.8833, -46, -47 }, { 1, 25.5000, 264, 268 }, { 0, 11.8667, 265, 267 }, { 0, 11.5167, -46, 266 }, { 1, 11.0000, -87, -46 }, { 1, 14.0000, -87, -25 }, { 1, 29.0000, 269, 271 }, { 0, 11.0000, -47, 270 }, { 0, 11.8667, -46, -25 }, { 0, 11.0000, -47, -84 }, { 0, 5.0000, 273, 322 }, { 1, 50.5000, 274, 296 }, { 0, 1.6667, 275, 284 }, { 1, 48.0000, 276, 281 }, { 0, 0.8667, 277, 279 }, { 0, 0.1667, -1, 278 }, { 1, 46.0000, -1, -18 }, { 0, 1.4083, -1, 280 }, { 1, 35.0000, -81, -1 }, { 1, 50.0000, 282, 283 }, { 0, 1.1167, -18, -1 }, { 0, 1.3667, -18, -63 }, { 0, 2.5667, 285, 291 }, { 1, 36.7500, 286, 288 }, { 0, 2.0000, 287, -81 }, { 1, 35.0000, -81, -1 }, { 0, 2.0417, 289, 290 }, { 1, 47.0000, -1, -63 }, { 0, 2.5167, -1, -63 }, { 0, 4.5000, 292, 294 }, { 0, 2.7167, 293, -63 }, { 1, 34.0000, -81, -63 }, { 0, 4.6917, 295, -8 }, { 1, 36.0000, -8, -63 }, { 1, 57.5000, 297, 309 }, { 0, 3.1667, 298, 305 }, { 0, 2.4333, 299, 303 }, { 1, 54.0000, 301, 302 }, { 0, 15.1607, 312, 307 }, { 0, 1.3667, -18, -63 }, { 0, 1.7000, -18, -63 }, { 1, 57.0000, -63, 304 }, { 0, 3.1000, -18, -11 }, { 1, 52.5000, 306, 307 }, { 0, 4.6917, -63, -8 }, { 0, 3.3333, 308, -11 }, { 1, 55.0000, -63, -11 }, { 1, 68.0000, 310, 316 }, { 0, 1.9083, 311, 313 }, { 0, 0.3333, 312, -18 }, { 1, 66.0000, -18, -20 }, { 0, 2.4333, 314, 315 }, { 1, 58.5000, -63, -18 }, { 0, 3.1000, -18, -11 }, { 1, 77.0000, 317, 319 }, { 0, 0.3333, -20, 318 }, { 0, 3.4167, -18, -11 }, { 1, 80.0000, 320, 321 }, { 0, 3.5083, -20, -11 }, { 1, 88.0000, -20, -85 }, { 1, 54.0000, 323, 343 }, { 0, 9.1667, 324, 334 }, { 1, 44.5000, 325, 329 }, { 1, 35.5000, 326, 328 }, { 0, 6.5333, -8, 327 }, { 0, 7.7500, -38, -51 }, { 0, 7.3667, -8, -51 }, { 0, 6.8000, 330, 332 }, { 0, 6.5000, -8, 331 }, { 1, 50.0000, -8, -51 }, { 0, 8.4167, -51, 333 }, { 1, 47.0000, -51, -84 }, { 0, 10.1667, 335, 339 }, { 1, 39.7500, 336, 337 }, { 0, 9.2500, -51, -47 }, { 1, 42.0000, 338, -84 }, { 0, 9.5833, -51, -47 }, { 0, 10.7833, 340, 341 }, { 1, 40.0000, -47, -84 }, { 0, 11.0000, 342, -84 }, { 1, 34.0000, -47, -84 }, { 1, 73.5000, 344, 353 }, { 0, 7.0000, 345, 348 }, { 0, 6.1000, 346, 347 }, { 1, 56.0000, -8, -11 }, { 1, 62.0000, -51, -11 }, { 0, 8.4167, 349, 351 }, { 1, 60.0000, -51, 350 }, { 0, 7.9667, -11, -84 }, { 0, 11.3333, -84, 352 }, { 1, 66.5000, -84, -34 }, { 1, 82.0000, 354, 359 }, { 0, 10.6667, 355, 356 }, { 0, 9.1667, -11, -34 }, { 0, 11.5000, 357, 358 }, { 1, 80.0000, -34, -11 }, { 1, 77.0000, -34, -11 }, { 0, 8.0000, 360, 362 }, { 1, 85.0000, -11, 361 }, { 1, 88.0000, -20, -85 }, { 1, 86.5000, -11, -85 }, { 0, 18.2500, 364, 538 }, { 1, -10.0000, 365, 449 }, { 0, 15.6667, 366, 407 }, { 1, -55.0000, 367, 386 }, { 1, -64.0000, 368, 378 }, { 0, 13.6667, 369, 373 }, { 1, -75.0000, 370, 371 }, { 1, -82.5000, -58, -22 }, { 0, 13.5000, -56, 372 }, { 1, -65.0000, -56, -23 }, { 1, -70.0000, 374, 375 }, { 1, -82.5000, -58, -3 }, { 1, -67.5000, 376, 377 }, { 0, 14.7500, -23, -82 }, { 0, 14.9167, -23, -82 }, { 0, 15.1667, 379, 383 }, { 0, 14.5333, 380, 381 }, { 0, 12.8333, -30, -19 }, { 0, 14.9167, -23, 382 }, { 1, -63.5833, -82, -23 }, { 0, 15.3333, 384, 385 }, { 1, -61.0000, -82, -23 }, { 1, -60.0000, -82, -57 }, { 1, -29.5000, 387, 398 }, { 1, -42.0000, 388, 393 }, { 0, 15.0500, 389, 390 }, { 0, 14.1667, -19, -50 }, { 0, 15.3333, 391, 392 }, { 1, -54.0000, -57, -50 }, { 1, -48.0000, -57, -50 }, { 0, 12.2500, 394, 395 }, { 1, -35.0000, -19, -42 }, { 0, 12.5833, 396, 397 }, { 1, -33.0000, -19, -42 }, { 0, 14.9167, -19, -50 }, { 0, 12.8333, 399, 403 }, { 1, -22.0000, 400, 402 }, { 0, 12.5833, 401, -42 }, { 1, -24.5000, -42, -28 }, { 1, -11.0000, -28, -87 }, { 0, 14.2500, 404, 405 }, { 1, -22.0000, -42, -87 }, { 0, 14.9167, 406, -49 }, { 1, -24.5000, -42, -49 }, { 1, -42.0000, 408, 430 }, { 1, -63.5833, 409, 419 }, { 1, -67.5000, 410, 415 }, { 0, 18.0000, 411, 414 }, { 1, -70.0000, 412, 413 }, { 1, -82.5000, -58, -3 }, { 0, 17.0000, -82, -3 }, { 1, -75.0000, -58, -61 }, { 0, 16.8333, 416, 418 }, { 0, 16.7500, -82, 417 }, { 1, -65.0000, -82, -6 }, { 0, 17.5000, -6, -61 }, { 1, -57.0000, 420, 425 }, { 0, 16.4208, 421, 422 }, { 1, -60.0000, -82, -57 }, { 0, 16.5833, 423, 424 }, { 1, -61.0000, -82, -6 }, { 0, 17.5000, -6, -61 }, { 1, -45.5000, 426, 428 }, { 0, 16.4208, -57, 427 }, { 0, 18.0000, -6, -80 }, { 0, 16.4208, -57, 429 }, { 0, 17.8333, -73, -26 }, { 0, 16.7500, 431, 440 }, { 0, 16.2667, 432, 436 }, { 1, -29.5000, 433, 434 }, { 0, 16.0000, -50, -73 }, { 0, 15.9167, 435, -73 }, { 1, -20.0000, -73, -49 }, { 1, -19.2500, 437, 438 }, { 1, -24.5833, -73, -59 }, { 0, 16.3750, 439, -59 }, { 1, -18.2500, -73, -59 }, { 1, -16.0000, 441, 445 }, { 0, 17.8333, 442, 444 }, { 1, -30.0000, -73, 443 }, { 0, 17.6000, -59, -72 }, { 1, -37.0000, -26, -72 }, { 0, 17.5833, 446, 447 }, { 0, 17.1667, -59, -77 }, { 0, 17.6667, 448, -77 }, { 1, -11.6667, -77, -59 }, { 0, 15.4333, 450, 495 }, { 1, 34.0000, 451, 473 }, { 0, 14.0333, 452, 463 }, { 1, 28.5000, 453, 458 }, { 0, 13.5000, 454, 457 }, { 0, 12.8333, 455, 456 }, { 1, 14.0000, -87, -25 }, { 1, 15.0000, -87, -25 }, { 1, 8.0000, -87, -9 }, { 0, 13.2500, 459, 461 }, { 0, 12.3333, -25, 460 }, { 1, 32.0000, -25, -13 }, { 0, 13.9583, -13, 462 }, { 1, 30.7500, -9, -13 }, { 0, 15.0833, 464, 469 }, { 1, -8.0000, 465, 466 }, { 0, 14.2500, -87, -49 }, { 1, 0.0000, 467, 468 }, { 0, 14.6667, -87, -49 }, { 1, 8.0000, -87, -9 }, { 1, 26.0000, 470, 471 }, { 1, -3.2500, -49, -76 }, { 0, 15.1833, -9, 472 }, { 1, 33.0000, -27, -9 }, { 1, 63.0000, 474, 484 }, { 0, 14.0333, 475, 480 }, { 0, 12.0833, 476, 477 }, { 1, 45.0000, -13, -84 }, { 0, 13.5000, 478, 479 }, { 1, 53.0000, -13, -84 }, { 1, 48.5000, -13, -84 }, { 1, 55.5000, 481, 483 }, { 0, 15.2500, -9, 482 }, { 1, 53.0000, -9, -34 }, { 0, 14.4167, -84, -34 }, { 1, 77.0000, 485, 491 }, { 1, 66.0000, 486, 488 }, { 0, 13.5000, 487, -34 }, { 1, 64.0000, -84, -34 }, { 1, 70.0000, 489, 490 }, { 0, 14.0000, -34, -85 }, { 0, 13.0000, -34, -85 }, { 1, 80.0000, 492, 493 }, { 0, 13.5833, -11, -85 }, { 0, 14.5000, 494, -85 }, { 1, 86.5000, -11, -85 }, { 1, 27.0000, 496, 517 }, { 1, 4.0000, 497, 506 }, { 0, 16.2667, 498, 502 }, { 0, 15.9167, 499, 500 }, { 1, -3.2500, -49, -76 }, { 1, -8.0000, -73, 501 }, { 1, -3.2500, -59, -76 }, { 1, -4.0000, 503, 504 }, { 0, 17.9667, -59, -77 }, { 0, 17.8333, -59, 505 }, { 1, 0.0000, -77, -59 }, { 1, 16.0000, 507, 512 }, { 0, 16.7500, 508, 509 }, { 0, 16.0833, -76, -40 }, { 0, 17.2500, 510, 511 }, { 1, 12.8333, -59, -40 }, { 1, 14.3333, -59, -40 }, { 1, 26.0000, 513, 516 }, { 1, 22.0000, 514, 515 }, { 0, 15.9167, -76, -40 }, { 0, 16.0333, -76, -40 }, { 0, 16.1667, -27, -40 }, { 1, 51.5000, 518, 527 }, { 0, 17.0000, 519, 522 }, { 1, 40.0000, 520, 521 }, { 0, 16.3333, -27, -40 }, { 0, 15.7500, -9, -40 }, { 1, 47.5000, 523, 525 }, { 0, 18.1750, -40, 524 }, { 1, 30.0000, -40, -52 }, { 0, 18.2333, 526, -34 }, { 1, 50.5000, -40, -34 }, { 0, 16.5333, 528, 533 }, { 1, 66.0000, 529, 531 }, { 0, 15.7500, 530, -34 }, { 1, 53.0000, -9, -34 }, { 0, 15.6667, -85, 532 }, { 1, 70.0000, -34, -85 }, { 1, 80.0000, 534, 536 }, { 0, 17.5000, 535, -34 }, { 1, 75.0000, -34, -85 }, { 0, 18.0000, -85, 537 }, { 1, 86.0000, -34, -85 }, { 1, 19.1667, 539, 620 }, { 1, -4.0000, 540, 576 }, { 0, 21.3333, 541, 558 }, { 1, -28.0000, 542, 551 }, { 1, -45.5000, 543, 548 }, { 0, 20.3333, 544, 546 }, { 1, -75.0000, -58, 545 }, { 1, -57.0000, -61, -80 }, { 1, -75.0000, -58, 547 }, { 1, -60.0000, -61, -44 }, { 0, 19.1667, 549, 550 }, { 1, -37.0000, -26, -72 }, { 0, 20.3333, -72, -54 }, { 0, 20.0000, 552, 555 }, { 0, 18.8667, 553, 554 }, { 1, -16.0000, -72, -75 }, { 1, -12.0333, -72, -5 }, { 0, 20.5333, 556, 557 }, { 1, -9.0000, -16, -5 }, { 1, -15.0000, -16, -4 }, { 1, -40.0000, 559, 568 }, { 1, -58.5000, 560, 564 }, { 1, -67.5000, 561, 563 }, { 1, -75.0000, -58, 562 }, { 0, 23.3333, -44, -83 }, { 0, 22.0000, -44, -83 }, { 0, 22.0000, 565, 566 }, { 1, -50.0000, -44, -39 }, { 0, 23.3333, 567, -64 }, { 1, -57.0000, -83, -39 }, { 1, -25.5000, 569, 572 }, { 1, -37.0000, 570, 571 }, { 0, 23.3333, -39, -74 }, { 0, 23.0000, -67, -74 }, { 0, 23.8333, 573, 575 }, { 0, 21.8667, 574, -4 }, { 1, -9.0000, -16, -4 }, { 1, -7.0000, -21, -66 }, { 0, 20.5333, 577, 598 }, { 0, 18.8667, 578, 588 }, { 1, 4.5000, 579, 583 }, { 0, 18.4250, 580, 581 }, { 1, 3.0000, -77, -59 }, { 0, 18.5833, -77, 582 }, { 1, 2.0000, -5, -77 }, { 0, 18.6622, 584, 586 }, { 1, 6.2500, -77, 585 }, { 1, 12.0000, -59, -40 }, { 1, 6.2500, -77, 587 }, { 1, 12.0000, -5, -40 }, { 1, 15.7500, 589, 593 }, { 0, 20.3000, 590, 592 }, { 0, 20.1417, -5, 591 }, { 1, 8.5000, -5, -32 }, { 1, 2.0000, -5, -32 }, { 0, 19.0000, 594, 595 }, { 1, 18.5000, -5, -71 }, { 0, 19.8333, 596, 597 }, { 1, 16.1667, -5, -71 }, { 0, 20.2500, -71, -32 }, { 0, 21.4667, 599, 611 }, { 0, 21.0500, 600, 605 }, { 1, 6.0000, 601, 603 }, { 1, 2.0000, -4, 602 }, { 0, 20.8333, -32, -35 }, { 0, 20.8750, -32, 604 }, { 1, 11.8333, -35, -32 }, { 1, 11.8333, 606, 608 }, { 1, 2.0000, -4, 607 }, { 0, 21.3333, -35, -62 }, { 0, 21.1167, -62, 609 }, { 0, 21.3333, 610, -62 }, { 1, 12.5000, -35, -62 }, { 0, 22.7500, 612, 617 }, { 0, 21.6667, 613, 614 }, { 1, 2.7500, -4, -62 }, { 0, 22.0000, 615, 616 }, { 1, 1.7500, -4, -62 }, { 1, 2.0000, -4, -62 }, { 0, 23.8333, 618, 619 }, { 1, 7.5000, -66, -62 }, { 1, 10.0000, -66, -62 }, { 1, 43.7500, 621, 666 }, { 0, 20.5667, 622, 645 }, { 0, 19.2583, 623, 632 }, { 0, 18.8667, 624, 627 }, { 0, 18.3667, 625, 626 }, { 1, 30.0000, -40, -52 }, { 1, 26.0000, -40, -52 }, { 1, 25.5000, 628, 630 }, { 0, 19.2500, 629, -89 }, { 1, 21.0833, -71, -89 }, { 0, 19.1667, -52, 631 }, { 1, 43.5000, -52, -31 }, { 0, 19.6667, 633, 639 }, { 1, 36.5000, 634, 637 }, { 1, 30.0000, 635, 636 }, { 1, 27.5000, -89, -31 }, { 0, 19.3583, -52, -31 }, { 0, 19.4000, 638, -31 }, { 1, 43.5000, -52, -31 }, { 0, 20.2500, 640, 643 }, { 1, 21.2500, 641, 642 }, { 0, 19.8333, -89, -71 }, { 1, 29.0000, -89, -31 }, { 1, 20.5000, -32, 644 }, { 1, 29.0000, -89, -31 }, { 0, 21.8750, 646, 656 }, { 1, 28.0000, 647, 652 }, { 0, 21.2500, 648, 650 }, { 1, 19.5000, 649, -89 }, { 0, 21.0500, -32, -62 }, { 0, 21.4167, 651, -62 }, { 1, 23.5000, -62, -89 }, { 0, 20.9167, 653, 654 }, { 1, 29.0000, -89, -31 }, { 0, 21.7333, -31, 655 }, { 1, 36.0000, -62, -31 }, { 1, 34.5000, 657, 661 }, { 0, 23.7500, 658, 660 }, { 0, 23.5000, -62, 659 }, { 1, 32.0833, -62, -1 }, { 1, 31.3333, -62, -1 }, { 0, 22.0000, 662, 663 }, { 1, 36.0000, -62, -45 }, { 0, 22.8167, 664, 665 }, { 1, 35.0000, -62, -45 }, { 0, 22.8667, -45, -1 }, { 0, 21.0000, 667, 689 }, { 1, 59.5000, 668, 677 }, { 0, 19.4167, 669, 673 }, { 1, 47.5000, 670, 671 }, { 0, 19.1667, -52, -31 }, { 0, 19.0833, -34, 672 }, { 1, 55.5000, -31, -34 }, { 0, 19.7667, 674, 675 }, { 1, 58.0000, -31, -34 }, { 0, 20.6000, -31, 676 }, { 1, 54.8333, -31, -20 }, { 1, 67.0000, 678, 684 }, { 0, 20.4167, 679, 681 }, { 0, 20.0000, -34, 680 }, { 1, 61.5000, -20, -34 }, { 0, 20.5367, -20, 682 }, { 0, 20.6000, 683, -20 }, { 1, 60.9167, -31, -20 }, { 1, 75.0000, 685, 686 }, { 0, 20.6667, -34, -20 }, { 1, 80.0000, 687, 688 }, { 0, 20.1667, -34, -20 }, { 1, 86.0000, -34, -85 }, { 0, 22.8667, 690, 701 }, { 1, 54.8333, 691, 696 }, { 0, 21.9667, 692, 694 }, { 0, 21.9083, -31, 693 }, { 1, 44.0000, -45, -31 }, { 0, 22.1333, 695, -45 }, { 1, 52.7500, -45, -20 }, { 1, 55.0000, 697, 698 }, { 0, 22.1333, -20, -45 }, { 1, 56.2500, 699, 700 }, { 0, 22.3167, -20, -45 }, { 1, 86.1667, -20, -85 }, { 1, 59.0833, 702, 707 }, { 1, 50.0000, 703, 705 }, { 0, 23.5833, -1, 704 }, { 1, 48.0000, -1, -18 }, { 0, 23.3333, 706, -18 }, { 1, 52.5000, -1, -18 }, { 1, 66.0000, 708, 711 }, { 1, 63.0000, 709, 710 }, { 0, 23.1667, -20, -18 }, { 0, 23.5833, -20, -18 }, { 0, 23.0000, 712, 713 }, { 1, 86.1667, -20, -85 }, { 1, 88.0000, -20, -85 } };

int GetConstellationIndex( double Rect, double Decl ) {
 Levels= 0;
 double P[2]= { Rect, Decl };
 int i= 0;
 while ( i >= 0 ) {
  Levels++;
  if ( P[Tree[i].iSplit] >= Tree[i].Split )
   i= Tree[i].nHi;
  else
   i= Tree[i].nLow;
 };
 return -i - 1;
}

int main( int argc, char **argv ) {
 double Rect;
 double Decl;

 if ( argc < 3 ) {
  printf( "Usage: %s R.A.[h,Decimal,B1875.0] Dec.[deg,Decimal,B1875.0]\n", argv[0] );
  return 1;
 }

 Rect= atof( argv[1] );
 if ( Rect < 0.0 || Rect > 24.0 ) {
  printf( "ERROR: the input R.A. is out of the expected range (0,24)\n" );
  return 1;
 }

 Decl= atof( argv[2] );
 if ( Decl < -90.0 || Decl > 90.0 ) {
  printf( "ERROR: the input Dec. is out of the expected range (-90,90)\n" );
  return 1;
 }

 // printf(" Equinox : B1875.0 \n");
 // printf(" Right Ascension [h,Decimal] : ");  scanf(" %lf",&Rect);
 // printf(" Declination [deg,Decimal]   : ");  scanf(" %lf",&Decl);

 // printf("\n Constellation: %s \n",&Names[GetConstellationIndex(Rect,Decl)]);
 // printf(" Found in %i steps.\n",Levels);
 // printf("%s\n", &Names[GetConstellationIndex(Rect,Decl)]);
 printf( "%s\n", Names[GetConstellationIndex( Rect, Decl )].cab );

 return 0;
}
