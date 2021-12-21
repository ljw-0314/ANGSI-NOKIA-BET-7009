// #ifndef MatrixInteFunc_H
// #define MatrixInteFunc_H

#include "MatrixInteFunc.h"

// Hardware model API declare
extern void MatrixCFG_core(unsigned int con_cfg, matrix_config *mat_cof);

// Hardware model API declare
extern void MatrixCFG_core0(unsigned int con_cfg, matrix_config *mat_cof, int *rst, int rQ, int is_real);


void MatrixADD_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_ADD << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);  //265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixSUB_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SUB << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}
void MatrixScaleADD_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SCALEADD << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleSUB_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SCALESUB << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMUL_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SCALEMUL << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMLA_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SCALEMLA << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMLS_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATR_SCALEMLS << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatVecMUL_Real(MXYZ *mx, MXYZ *my, int *rst, MC *mc, int rQ)
{
	MC mc;
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;

	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATRVECT_MUL << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;

	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core0(Con_cfg, matrix_config0, rst, rQ, 1);
}

void MatrixMUL_Real(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc, int rQ)
{
	matrix_config *matrix_config0;

	int *ptr1;
	int i, j;

	ptr1 = NULL;
	MC *mc1;
	MXYZ *mx1;
	MXYZ *my1;

	mc1->MatRow = 0;
	mc1->MatCol = mc->MatCol;

	mx1->Dw = mx->Dw;
	mx1->Conj = mx->Conj;
	mx1->RowStep = mx->RowStep;
	mx1->ColStep = mx->ColStep;

	my1->Dw = my->Dw;
	my1->Conj = my->Conj;
	my1->RowStep = my->ColStep;
	my1->ColStep = my->RowStep;

	for (i = 0; i <= mc->MatRow; i++)
	{
		for (j = 0; j <= mc->MatRow; j++)
		{
			mx1->MatAdr = (unsigned int)(mx->MatAdr + i * mx->RowStep * (mc->MatCol + 1));
			my1->MatAdr = (unsigned int)(my->MatAdr + j * my->RowStep);
			ptr1 = (int *)(mz->MatAdr + j * mz->RowStep + i * mz->RowStep * (mc->MatRow + 1));
			MatVecMUL_Real(mx1, my1, ptr1, mc1, rQ);
		}
	}
}

void MatrixADD_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_ADD << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixSUB_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SUB << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleADD_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SCALEADD << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleSUB_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SCALESUB << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixComplexScaleMUL_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_CSCALEMUL << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMUL_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SCALEMUL << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMLA_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SCALEMLA << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatrixScaleMLS_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc)
{
	matrix_config *matrix_config0;

	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATC_SCALEMLS << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;
	matrix_config0->matrix_zadr = (unsigned int)mz->MatAdr;

	matrix_config0->matrix_rs = mc->RS;
	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);
	matrix_config0->matrix_zconfig = (mz->Dw << 29) | ((mz->ColStep & 0xFFF) << 12) | (mz->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core(Con_cfg, matrix_config0);
}

void MatVecMUL_Complex(MXYZ *mx, MXYZ *my, int *rst, MC *mc, int rQ)
{
	matrix_config *matrix_config0;
	unsigned int Con_cfg = 0;
	matrix_config0->matrix_con = 0;

	matrix_config0->matrix_con = (MATCVECT_MUL << 26) | ((mc->MatQ & 0x3F) << 20) | (mc->MatCol << 10) | (mc->MatRow);
	matrix_config0->matrix_xadr = (unsigned int)mx->MatAdr;
	matrix_config0->matrix_yadr = (unsigned int)my->MatAdr;

	matrix_config0->matrix_xconfig = (mx->Dw << 29) | (mx->Conj << 28) | ((mx->ColStep & 0xFFF) << 12) | (mx->RowStep & 0xFFF);
	matrix_config0->matrix_yconfig = (my->Dw << 29) | (my->Conj << 28) | ((my->ColStep & 0xFFF) << 12) | (my->RowStep & 0xFFF);

	Con_cfg = (1 << 8) | (0 << 6) | (1 << 3) | (0 << 2) | (0 << 1) | (1 << 0);	//265

	MatrixCFG_core0(Con_cfg, matrix_config0, rst, rQ, 0);

	
}

void MatrixMUL_Complex(MXYZ *mx, MXYZ *my, MXYZ *mz, MC *mc, int rQ)
{
	matrix_config *matrix_config0;

	int *ptr;
	int i, j;

	ptr = NULL;
	MC *mc1;
	MXYZ *mx1;
	MXYZ *my1;

	mc1->MatRow = 0;
	mc1->MatCol = mc->MatCol;

	mx1->Dw = mx->Dw;
	mx1->Conj = mx->Conj;
	mx1->RowStep = mx->RowStep;
	mx1->ColStep = mx->ColStep;

	my1->Dw = my->Dw;
	my1->Conj = my->Conj;
	my1->RowStep = my->ColStep;
	my1->ColStep = my->RowStep;

	for (i = 0; i <= mc->MatRow; i++)
	{
		for (j = 0; j <= mc->MatCol; j++)
		{
			mx1->MatAdr = (unsigned int)(mx->MatAdr + i * mx->RowStep * mc->MatCol);
			my1->MatAdr = (unsigned int)(my->MatAdr + j * mc->MatRow);
			ptr = (int *)(mz->MatAdr + j * mz->RowStep + i * mz->RowStep * mc->MatCol);

			MatVecMUL_Complex(mx1, my1, ptr, mc1, rQ);
		}
	}
}

// #endif