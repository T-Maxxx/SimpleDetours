#include "HookBase.h"
//TODO: add this to handler, fill up .cpp
//TODO: CallHook
//TODO: add CallHook to handler
namespace SimpleDetours
{
	class SIMPLEDETOURS_API JumpHook : public HookBase
	{
	public:
		JumpHook();
		JumpHook(MultiPointer from, MultiPointer to);
		~JumpHook();

		void initialize(MultiPointer from, MultiPointer to);
		void setupHook();
		void removeHook();
		dword version();
	private:
		MultiPointer place;
		MultiPointer target;
		MultiPointer originalCode;
	};
}
