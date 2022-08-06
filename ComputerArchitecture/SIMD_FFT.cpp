//https://duck.ac/submission/17603
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<random>
#include<immintrin.h>
#include<emmintrin.h>

#pragma GCC target("avx2")
#pragma GCC optimize("-fno-strict-aliasing")

#define LL long long S
#define UL unsigned LL
#define U unsigned
#define S int
#define fr(i,l) for(S i=0;i<l;i++)

#define Prefetch(p) _mm_prefetch(p,_MM_HINT_T0)

constexpr U mod=10223617u;
constexpr U g=5u;
constexpr U gi=4089447u;

struct ymm
{
    __m256i x;
    ymm(){}
    ymm(__m256i x):x(x){}
    ymm(const void*p):x(*(__m256i*)p){}
    ymm(U x):x(_mm256_set1_epi32(x)){}
    operator __m256i(){return x;}
    void store(void*p) const {*(__m256i*)p=x;}
};
ymm p1_vec(0xffffffffu);
ymm p0_vec(0u);
inline ymm operator+(ymm a,ymm b){return _mm256_add_epi32(a,b);}
inline ymm operator-(ymm a,ymm b){return _mm256_sub_epi32(a,b);}
inline ymm operator*(ymm a,ymm b){return _mm256_mul_epu32(a,b);}
inline ymm operator|(ymm a,ymm b){return _mm256_or_si256(a,b);}
inline ymm operator&(ymm a,ymm b){return _mm256_and_si256(a,b);}
inline ymm andnot(ymm a,ymm b){return _mm256_andnot_si256(a,b);}
inline ymm operator~(ymm a){return andnot(a,p1_vec);}
inline ymm operator>(ymm a,ymm b){return _mm256_cmpgt_epi32(a,b);}
inline ymm operator==(ymm a,ymm b){return _mm256_cmpeq_epi32(a,b);}
inline ymm operator>>(ymm a,int w){return _mm256_srli_epi32(a,w);}
inline ymm operator<<(ymm a,int w){return _mm256_slli_epi32(a,w);}
template<U mask>
inline ymm blend(ymm a,ymm b){return _mm256_blend_epi32(a,b,mask);}
inline ymm blendv(ymm a,ymm b,ymm mask){return _mm256_blendv_epi8(a,b,mask);}
template<U mask>
inline ymm permute2x128(ymm a,ymm b){return _mm256_permute2x128_si256(a,b,mask);}

inline ymm rmov(ymm a,int w){return _mm256_srli_epi64(a,w);}
inline ymm lmov(ymm a,int w){return _mm256_slli_epi64(a,w);}
template<int w>
inline ymm rmov128(ymm a){return _mm256_bsrli_epi128(a,w);}
template<int w>
inline ymm lmov128(ymm a){return _mm256_bslli_epi128(a,w);}
inline ymm mullo(ymm a,ymm b){return _mm256_mullo_epi32(a,b);}

ymm mod1_vec(mod-1);
ymm mod_vec(mod);
ymm mod_inv_vec(881018846u);

U mo(U x){return x>=mod?x-mod:x;}

inline ymm jmod(ymm a){return a-(a>mod1_vec&mod_vec);}

inline ymm mul_mod(ymm a,ymm b)
{
    static constexpr U mask=0xaa;
    ymm t1=a*b;
    ymm t2=rmov(a,32)*rmov(b,32);
    ymm abl=blend<mask>(t1,lmov(t2,32));
    ymm abh=blend<mask>(rmov(t1,21),lmov(t2,11));
    ymm ab_p=blend<mask>(rmov(abh*mod_inv_vec,32),rmov(abh,32)*mod_inv_vec);
    a=abl-mullo(ab_p,mod_vec);
    return jmod(a);
}

U pow(U a,U b)
{
    U ans=1;
    for(;b;a=(UL)a*a%mod,b>>=1)
        if(b&1)ans=(UL)ans*a%mod;
    return ans;
}

U& mul(U&a,U b){return a=(UL)a*b%mod;}
S up(S x){S l=1;while(l<x)l<<=1;return l;}

constexpr S ml=1<<21;
alignas(64) U wr[ml+16],wi[ml+16];

void init(S ml)
{
    for(S len=1;len<ml;len<<=1)
    {
        U Wr=pow(g,(mod-1)/(len<<1));
        U Wi=pow(gi,(mod-1)/(len<<1));
        if(len<8)
        {
            U tr=1,ti=1;
            fr(i,len)
            {
                wr[len+i]=tr;mul(tr,Wr);
                wi[len+i]=ti;mul(ti,Wi);
            }
        }
        else
        {
            {
                U tr=1,ti=1;
                fr(i,8)
                {
                    wr[len+i]=tr;mul(tr,Wr);
                    wi[len+i]=ti;mul(ti,Wi);
                }
            }
            ymm tr(wr+len),ti(wi+len),Wr_vec(pow(Wr,8)),Wi_vec(pow(Wi,8));
            for(int i=8;i<len;i+=8)
            {
                tr=mul_mod(Wr_vec,tr);tr.store(wr+len+i);
                ti=mul_mod(Wi_vec,ti);ti.store(wi+len+i);
            }
        }
    }
}
void NTTfa(U*a,S len)
{
    for(S i=len>>1;i;i>>=1)
    {
        if(i==1)
        {
            auto trans1=[](U*p)
            {
                ymm x(p);
                jmod(blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec)).store(p);
            };
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans1(a+j);
                trans1(a+j+8);
            }
        }
        else if(i==2)
        {
            auto trans2=[](U*xp,U*yp,ymm w)
            {
                ymm x(xp),y(yp);
                ymm t1(blend<0xcc>(x,lmov128<8>(y)));
                ymm t2(blend<0x33>(y,rmov128<8>(x)));
                x=jmod(t1+t2);
                y=mul_mod(t1-t2+mod_vec,w);
                blend<0xcc>(x,lmov128<8>(y)).store(xp);
                blend<0x33>(y,rmov128<8>(x)).store(yp);
            };
            ymm w=_mm256_set_epi32(wr[3],wr[2],wr[3],wr[2],wr[3],wr[2],wr[3],wr[2]);
            for(int j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans2(a+j,a+j+8,w);
            }
        }
        else if(i==4)
        {
            auto trans4=[](U*xp,U*yp,ymm w)
            {
                ymm tx(xp),ty(yp);
                ymm x(permute2x128<0x20>(tx,ty));
                ymm y(permute2x128<0x31>(tx,ty));
                tx=jmod(x+y);
                ty=mul_mod(x-y+mod_vec,w);
                x=permute2x128<0x20>(tx,ty);
                y=permute2x128<0x31>(tx,ty);
                x.store(xp);
                y.store(yp);
            };
            ymm w=_mm256_set_epi32(wr[7],wr[6],wr[5],wr[4],wr[7],wr[6],wr[5],wr[4]);
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans4(a+j,a+j+8,w);
            }
        }
        else
        {
            auto trans=[](U*xp,U*yp,const U*wp)
            {
                ymm x(xp),y(yp),w(wp);
                jmod(x+y).store(xp);
                mul_mod(x-y+mod_vec,w).store(yp);
            };
            if(i==8)
            {
                for(S j=0;j<len;j+=16)
                {
                    Prefetch(a+j+16);
                    trans(a+j,a+j+8,wr+8);
                }
            }
            else
            {
                
                for(S j=0;j<len;j+=i<<1)
                {
                    for(S k=0;k<i;k+=16)
                    {
                        Prefetch(a+j+k+16);
                        trans(a+j+k,a+j+k+i,wr+i+k);
                        Prefetch(a+j+k+i+16);
                        trans(a+j+k+8,a+j+k+i+8,wr+i+k+8);
                    }
                }

            }
        }
    }
}
void NTTifa(U*a,S len)
{
    for(S i=1;i<len;i<<=1)
    {
        if(i==1)
        {
            auto trans1=[](U*p)
            {
                ymm x(p);
                blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec).store(p);
            };
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans1(a+j);
                trans1(a+j+8);
            }
        }
        else if(i==2)
        {
            auto trans2=[](U*xp,U*yp,ymm w)
            {
                ymm x(xp),y(yp);
                ymm t1(blend<0xcc>(x,lmov128<8>(y)));
                ymm t2(blend<0x33>(y,rmov128<8>(x)));
                t2=mul_mod(t2,w);
                x=t1+t2;
                y=t1-t2+mod_vec;
                blend<0xcc>(x,lmov128<8>(y)).store(xp);
                blend<0x33>(y,rmov128<8>(x)).store(yp);
            };
            ymm w=_mm256_set_epi32(wi[3],wi[2],wi[3],wi[2],wi[3],wi[2],wi[3],wi[2]);
            for(int j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans2(a+j,a+j+8,w);
            }
        }
        else if(i==4)
        {
            auto trans4=[](U*xp,U*yp,ymm w)
            {
                ymm tx(xp),ty(yp);
                ymm x(permute2x128<0x20>(tx,ty));
                ymm y(permute2x128<0x31>(tx,ty));
                y=mul_mod(y,w);
                tx=x+y;
                ty=x-y+mod_vec;
                x=permute2x128<0x20>(tx,ty);
                y=permute2x128<0x31>(tx,ty);
                x.store(xp);
                y.store(yp);
            };
            ymm w=_mm256_set_epi32(wi[7],wi[6],wi[5],wi[4],wi[7],wi[6],wi[5],wi[4]);
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans4(a+j,a+j+8,w);
            }
        }
        else
        {
            auto trans=[](U*xp,U*yp,const U*wp)
            {
                ymm y(yp),w(wp);
                y=mul_mod(y,w);
                ymm x(xp);
                (x+y).store(xp);
                (x-y+mod_vec).store(yp);
            };
            if(i==8)
            {
                for(S j=0;j<len;j+=16)
                {
                    Prefetch(a+j+16);
                    trans(a+j,a+j+8,wi+8);
                }
            }
            else
            {
                
                for(S j=0;j<len;j+=i<<1)
                {
                    for(S k=0;k<i;k+=16)
                    {
                        Prefetch(a+j+k+16);
                        trans(a+j+k,a+j+k+i,wi+i+k);
                        Prefetch(a+j+k+i+16);
                        trans(a+j+k+8,a+j+k+i+8,wi+i+k+8);
                    }
                }

            }
        }
    }
    
    ymm inv(pow(len,mod-2));
    for(S i=0;i<len;i+=8)
        mul_mod(a+i,inv).store(a+i);
    
    /*
    int k=__builtin_ctz(len);
    ymm k1_vec((U)(len-1));
    ymm v1_vec(1u);
    for(S i=0;i<len;i+=8)
    {
        ymm x(a+i);
        ymm t(p0_vec-x&k1_vec);
        jmod((x+t>>k)+mullo(mod_vec>>k,t)).store(a+i);
    }
    */
}

int n,m;
//#define TEST_JUDGE 1000000
alignas(64) U a[ml+16],b[ml+16],c[ml+16];

struct buf{
    char a[1<<25],*s,*t;
    buf():s(a),t(a){
        a[fread(a,1,sizeof a,stdin)]=0;
    }
    ~buf(){fwrite(a,1,t-a,stdout);}
    operator U(){
        int x=0;
        while(*s>47)
            x=x*10+*s++-48; ++s;
        return x;
    }
    void out(U n){
        #define pyo(x) *t++=x
    switch(n) {
    case 1000000000 ... 2147483647:
        pyo(48+n/1000000000); n%=1000000000;
    case 100000000 ... 999999999:
        pyo(48+n/100000000); n%=100000000;
    case 10000000 ... 99999999:
        pyo(48+n/10000000); n%=10000000;
    case 1000000 ... 9999999:
        pyo(48+n/1000000); n%=1000000;
    case 100000 ... 999999:
        pyo(48+n/100000); n%=100000;
    case 10000 ... 99999:
        pyo(48+n/10000); n%=10000;
    case 1000 ... 9999:
        pyo(48+n/1000); n%=1000;
    case 100 ... 999:
        pyo(48+n/100); n%=100;
    case 10 ... 99:
        pyo(48+n/10); n%=10;
    }
    pyo(48+n);
    pyo(32);
    }
}it;


int main()
{
    n=it;
    m=it;
    for(int i=0;i<=n;i++)
        a[i]=it;
    for(int j=0;j<=m;j++)
        b[j]=it;

    int len=n+m+1;
    int k=32;
    while(k<len)k<<=1;

    init(k);
    NTTfa(a,k);
    NTTfa(b,k);
    for(S i=0;i<k;i+=8)
        mul_mod(a+i,b+i).store(a+i);
    NTTifa(a,k);
    for(int i=0;i<len;i++)
        it.out(a[i]);
}
/*
file input:
1 2
1 2
1 2 1


out put:
1 4 5 2
*/