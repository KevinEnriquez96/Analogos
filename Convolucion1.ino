#define ARM_MATH_CM3 
#include <arm_math.h>
#define SIG_TAM 320
#define IMP_TAM 29
#define PULSE_TAM 100 
extern float32_t InputSignal_1kHz_15kHz [SIG_TAM] ;
extern float32_t Impulse_response [IMP_TAM] ;
extern float32_t ECG_100pts[100] ;
float32_t Output_Signal [SIG_TAM+IMP_TAM] ;
void plot (void) ;
void convolucion (float32_t *sig_in,
                  float32_t *sig_imp,
                  float32_t *sig_out,
                  uint32_t tam_sig,
                  uint32_t tam_imp
                        ) ;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600) ;

}

void loop() {
  // put your main code here, to run repeatedly:
//  convolucion ((float32_t*)& ECG_100pts [0] ,
//               (float32_t*)&InputSignal_1kHz_15kHz[0],
//               (float32_t*)&Output_Signal[0],
//               (uint32_t) SIG_TAM,
//               (uint32_t) IMP_TAM) ;
  plot () ;
  //LIBRERIA
  arm_conv_f32(&ECG_100pts[0],PULSE_TAM,&Impulse_response[0],IMP_TAM,&Output_Signal[0]) ;

}
void plot () {
  uint32_t i ;
for (i=0; i<SIG_TAM ; i++) {
  Serial.println (Output_Signal[i]) ;
  delay (15) ;
}
}
void convolucion (float32_t *sig_in,
                  float32_t *sig_imp,
                  float32_t *sig_out,
                  uint32_t tam_sig,
                  uint32_t tam_imp
                        ) {
  uint32_t i,j ;
  //llenras de ceros el vector de salidas
  for (i=0;i<(tam_sig+tam_imp);i++) {
    sig_out [i] =0 ;
  }
  for (i=0;i<tam_sig;i++) {
    for (j=0;j<tam_imp;j++) {
      sig_out[i+j]-sig_out[i+j]+sig_in[i]*sig_imp[j] ;
    }
  }
  
}
