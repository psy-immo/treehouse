/**
 * math.c, (c) 2014, Immanuel Albrecht; Dresden University of
 * Technology, Professur für die Psychologie des Lernen und Lehrens
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "hygra.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int number_of_m_to_n_surjections(int m, int n) {
    /**
     * The Mathematical Gazette, Vol. 63, No. 426 (Dec., 1979)
     *   contains: 63.29 Surjections from an m-Set to an n-Set
     * F. Gerrish
     * pp. 259-261 (3 pages)
     */
     
     int k, e_mn, n_over_k, k_to_the_mth, summand, i;
     
     if (m < n)
         return 0;
        
     e_mn = 0;
         
     
     for (k=1;k<=n;++k) {
         
         k_to_the_mth = 1;
         for (i=0;i<m;++i) {
            k_to_the_mth *= k;
         }
         
         n_over_k = 1;
         for (i=1;i<=k;++i) {
             n_over_k *= n+1-i;
         }
         
         for (i=1;i<=k;++i) {
             n_over_k /= i;
         }
         
         summand = n_over_k * k_to_the_mth;
         if ((n-k)%2) {
             e_mn -= summand;
         } else {
             e_mn += summand;
         }
     }
              
    return e_mn;
}