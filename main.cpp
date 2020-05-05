/*
 * Copyright (c) 2020, Michael Grand
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"

extern "C" {
#include "mbed-se050-drv/se050.h"
#include "sensor.h"
#include "util.h"
}

int main(void)
{
	apdu_ctx_t ctx;

	printf("lets go!\n");

	if(MBED_SUCCESS != connect(&ctx)) {
		perror("Can't connect to SE050 \n");
		return -1;
	}

	attestation_t attestation = {0};
	uint16_t temperature;

	while(1) {
	    printf("\nRead SE050 attested PmodTMP3 temperature\n");
	    printf("------------------------------------------\n");
	    getTemp(&ctx, &temperature, &attestation);
		printf("Temperature: %x\n\n", temperature);
		printByteArray("ChipId", &attestation.chipId[0], 18);
		printByteArray("Random", &attestation.outrandom[0], 16);
		printByteArray("TimeStamp", &attestation.timeStamp[0], 12);
		printByteArray("Signature", &attestation.signature.p_data[0], attestation.signature.len);
		printByteArray("Data", &ctx.out.p_data[0], ctx.out.len);
		printf("SW = %x\n", ctx.sw);
		thread_sleep_for(1000);
	}
	return 0;
}
